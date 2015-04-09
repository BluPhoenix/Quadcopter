	.include "m48def.inc"	

	.def temp 	= r16
	.def mc1 	= r17
	.def mc2 	= r18
	.def mc3 	= r19
	.def mc4 	= r20
	.def m1 	= r21
	.def m2  	= r22
	.def m3  	= r23
	.def m4  	= r24
	.def state 	= r25

	.org 0x00
		rjmp main
	.org SPIaddr
		rjmp SPI_Receive
	.org OC0Aaddr	; Timer 0 Output Compare A
		rjmp Decrease_Counters
	.org OC1Aaddr
		rjmp Reset_Counters

	.org INT_VECTORS_SIZE

main:
	ldi temp, (1<<CLKPCE) ; Changing the Clock divider requires setting the CLKPCE bit first
	sts CLKPR, temp
	ldi temp, 0x00
	sts CLKPR, temp ; Set Clock Divider to 1, standard is 8

	ldi state, 0x00 ; State stores which Motor Setting the next SPI command changes
	ldi mc1, 0x00	; m1 = C.3
	ldi mc2, 0x00	; m2 = C.2
	ldi mc3, 0x00	; m3 = C.1
	ldi mc4, 0x00	; m4 = C.0
	ldi m1,  100
	ldi m2,  100
	ldi m3,  100
	ldi m4,  100

	ldi temp, (1<<PC0) + (1<<PC1) + (1<<PC2) + (1<<PC3) ; Enable pins C.0-C.3 for output
	out DDRC, temp


	ldi temp, (1<<PD6)
	out DDRD, temp
	
						; Init Timer 0 to fire every 10 us
	ldi temp, (1<<COM0A0) +  (1<<WGM01); Clear Timer on Compare Match
	out TCCR0A, temp
	ldi temp, (1<<CS00)	; No clock prescaling
	out TCCR0B, temp
	ldi temp, 80		; 80 cycles at 8MHz = 10 us
	out OCR0A, temp
	ldi temp, (1<<OCIE0A)
	sts TIMSK0, temp ; TIMSK0 out of range for "out"


						; Init Timer 1 to fire every 20 ms
	ldi temp, (1<<WGM12) + (1<<CS12) + (1<<CS10); Clock divider: 1024
	sts TCCR1B, temp
	ldi temp, 0x00
	sts OCR1AH, temp
	ldi temp, 162		; 0.02 = 156 / (8.000.000 / 1024) but the oscilloscope says 165 is better
	sts OCR1AL, temp
	ldi temp, (1<<OCIE1A)
	sts TIMSK1, temp 	; Enable Compare interrupt


						; Init SPI
	ldi temp, (1<<DDB4) ; MISO
	out DDRB, temp
	ldi temp, (1<<SPE) + (1<<SPIE)
	out SPCR, temp

	sei					; Enable Interrupts


m1:					; Main loop
	cpi mc1, 0x00	; Compares each motor counter and sets/clears bits
	breq m1zero
	sbi PORTC, PC3
	jmp m2
m1zero:
	cbi PORTC, PC3
m2:
	cpi mc2, 0x00
	breq m2zero
	sbi PORTC, PC2
	jmp m3
m2zero:
	cbi PORTC, PC2
m3:
	cpi mc3, 0x00
	breq m3zero
	sbi PORTC, PC1
	jmp m4
m3zero:
	cbi PORTC, PC1
m4:
	cpi mc4, 0x00
	breq m4zero
	sbi PORTC, PC0
	jmp m1
m4zero:
	cbi PORTC, PC0
	
	jmp m1			; Main loop end

Decrease_Counters: 	; Decreases mc* if not zero, called by timer interrupt
	cpi mc1, 0x00
	breq mc2
	dec mc1
mc2:
	cpi mc2, 0x00
	breq mc3
	dec mc2
mc3:
	cpi mc3, 0x00
	breq mc4
	dec mc3
mc4:
	cpi mc4, 0x00
	breq DC_end
	dec mc4
DC_end:
	reti

Reset_Counters:
	mov mc1, m1
	mov mc2, m2
	mov mc3, m3
	mov mc4, m4
	reti


SPI_Receive:
	in temp, SPDR
	cpi temp, 0x05	; >= 5 sets the speed of the selected motor, <5 selects a motor
	brlo selectmotor
	
	dec state		; Change Speed Switch
	breq setm1
	dec state
	breq setm2
	dec state
	breq setm3
	mov m4, temp ; else
	reti
setm1:
	mov m1, temp
	reti
setm2:
	mov m2, temp
	reti
setm3:
	mov m3, temp
	reti
selectmotor:
	mov state, temp
	reti
