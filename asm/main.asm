	.include "m48def.inc"	
	.org 0x00
		rjmp main
	.org SPIaddr
		rjmp SPI_Receive

main:	ldi r16, (1<<PD7)
	out DDRD, r16
	ldi r18, 0b10000000
	out PORTD, r18
	rcall SPI_SlaveInit
loop:	rjmp loop

SPI_SlaveInit:
	ldi r17, (1<<DDB4)
	out DDRB, r17
	ldi r17, (1<<SPE) | (1<<SPIE)
	out SPCR, r17
	sei
	ret

SPI_Receive:
	in r18, SPDR
	cpi r18, 0x0F
	brge load
	ldi r18, 0b10000000
	rjmp set
load:	ldi r18, 0x00
set:	out PORTD, r18
	reti
