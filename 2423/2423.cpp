#include "spi.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define CE_PIN 5

void Set_CE()
{
	char buf[100];
	int bytes = sprintf(buf, "/sys/class/gpio/gpio%d/value", CE_PIN);
	int fd = open(buf, O_WRONLY);
	if (fd < 0)
	{
		printf("Error setting ce\n");
		return;
	}
	int res = write(fd, "1", 1);
	if (res < 0)
	{
		printf("Error writing to ce");
	}
}

void Reset_CE()
{
	char buf[100];
	int bytes = sprintf(buf, "/sys/class/gpio/gpio%d/value", CE_PIN);
	int fd = open(buf, O_WRONLY);
	if (fd < 0)
	{
		printf("Error resetting ce\n");
		return;
	}
	int res = write(fd, "0", 1);
	if (res < 0)
	{
		printf("Error writing to ce");
	}
}

void InitChip(Spi *s)
{
	unsigned char buf[12];
	buf[0] = 0xFF; // Status
	s->Transfer(buf, 1);
	if (buf[0] & 0x80) // Regiser Bank 1 activated
	{
		buf[0] = 0x50; // Activate
		buf[1] = 0x53; // Toggle Register Bank
		s->Transfer(buf, 2);
	}
	buf[0] = 0x24; // Transmission Delay
	buf[1] = 0xFF; // 4000µS
	s->Transfer(buf, 2);
	buf[0] = 0x25; //WR Channel
	buf[1] = 0x08; // Channel 8
	s->Transfer(buf, 2);
	buf[0] = 0x26; // RF Setup
	buf[1] = 0x03; // 1Mbps, -12dBm
	s->Transfer(buf, 2);
	
	// Should be unnecessary but nvm
	// Setting LSByte of P2-P5
	buf[0] = 0x2C;
	buf[1] = 0xC3;
	s->Transfer(buf, 2);
	buf[0] = 0x2D;
	buf[1] = 0xC4;
	s->Transfer(buf, 2);
	buf[0] = 0x2E;
	buf[1] = 0xC5;
	s->Transfer(buf, 2);
	buf[0] = 0x2F;
	buf[1] = 0xC6;
	s->Transfer(buf, 2);


	buf[0] = 0x31; // RX Payload Size (P0)
	buf[1] = 0x10; // 16 Byte
	s->Transfer(buf, 2);
	// Should be unnecessary but...
	// RX Payload Sizes for P1 - P5
	buf[0] = 0x32;
	buf[1] = 0x10;
	s->Transfer(buf, 2);
	buf[0] = 0x33;
	buf[1] = 0x10;
	s->Transfer(buf, 2);
	buf[0] = 0x34;
	buf[1] = 0x10;
	s->Transfer(buf, 2);
	buf[0] = 0x35;
	buf[1] = 0x10;
	s->Transfer(buf, 2);
	buf[0] = 0x36;
	buf[1] = 0x10;
	s->Transfer(buf, 2);
	buf[0] = 0x37;
	buf[1] = 0x00;
	s->Transfer(buf, 2);


	buf[0] = 0x2A; // RX Address P0
	buf[1] = 0x66; 
	buf[2] = 0x88; 
	buf[3] = 0x68; 
	buf[4] = 0x68; 
	buf[5] = 0x68; 
	s->Transfer(buf, 6);
	// Should be unneccessary RX Address P1
	buf[0] = 0x2B;
	buf[1] = 0x88; 
	buf[2] = 0x66; 
	buf[3] = 0x86; 
	buf[4] = 0x86; 
	buf[5] = 0x86; 
	s->Transfer(buf, 6);
	buf[0] = 0x30; // TX Address
	buf[1] = 0x66; 
	buf[2] = 0x88; 
	buf[3] = 0x68; 
	buf[4] = 0x68; 
	buf[5] = 0x68; 
	s->Transfer(buf, 6);
	// Magic that is only partly documented in the Datasheet
	buf[0] = 0x50; // Activate
	buf[1] = 0x53; // Switch Register Bank
	s->Transfer(buf, 2);
	buf[0] = 0x20;
	buf[1] = 0x40;
	buf[2] = 0x4B;
	buf[3] = 0x01;
	buf[4] = 0xE2;
	s->Transfer(buf, 5);
	buf[0] = 0x21;
	buf[1] = 0xC0;
	buf[2] = 0x4B;
	buf[3] = 0x00;
	buf[4] = 0x00;
	s->Transfer(buf, 5);
	buf[0] = 0x22;
	buf[1] = 0xD0;
	buf[2] = 0xFC;
	buf[3] = 0x8C;
	buf[4] = 0x02;
	s->Transfer(buf, 5);
	buf[0] = 0x23;
	buf[1] = 0xF9;
	buf[2] = 0x00;
	buf[3] = 0x39;
	buf[4] = 0x21;
	s->Transfer(buf, 5);
	buf[0] = 0x24;
	buf[1] = 0xC1;
	buf[2] = 0x96;
	buf[3] = 0x9A;
	buf[4] = 0x1B;
	s->Transfer(buf, 5);
	buf[0] = 0x25;
	buf[1] = 0x24;
	buf[2] = 0x06;
	buf[3] = 0x7F;
	buf[4] = 0xA6;
	s->Transfer(buf, 5);
	buf[0] = 0x26;
	buf[1] = 0x00;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	s->Transfer(buf, 5);
	buf[0] = 0x27;
	buf[1] = 0x00;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	s->Transfer(buf, 5);
	buf[0] = 0x28;
	buf[1] = 0x00;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	s->Transfer(buf, 5);
	buf[0] = 0x29;
	buf[1] = 0x00;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	s->Transfer(buf, 5);
	buf[0] = 0x2A;
	buf[1] = 0x00;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	s->Transfer(buf, 5);
	buf[0] = 0x2B;
	buf[1] = 0x00;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	s->Transfer(buf, 5);
	buf[0] = 0x2C;
	buf[1] = 0x00;
	buf[2] = 0x12;
	buf[3] = 0x73;
	buf[4] = 0x00;
	s->Transfer(buf, 5);
	buf[0] = 0x2D;
	buf[1] = 0x46;
	buf[2] = 0xB4;
	buf[3] = 0x80;
	buf[4] = 0x00;
	s->Transfer(buf, 5);
	buf[0] = 0x2E;
	buf[1] = 0x41;
	buf[2] = 0x10;
	buf[3] = 0x04;
	buf[4] = 0x82;
	buf[5] = 0x20;
	buf[6] = 0x08;
	buf[7] = 0x08;
	buf[8] = 0xF2;
	buf[9] = 0x7D;
	buf[10]= 0xEF;
	buf[11]= 0xFF;
	s->Transfer(buf, 12);
	buf[0] = 0x24;
	buf[1] = 0xC7;
	buf[2] = 0x96;
	buf[3] = 0x9A;
	buf[4] = 0x1B;
	s->Transfer(buf, 5);
	buf[0] = 0x24;
	buf[1] = 0xC1;
	buf[2] = 0x96;
	buf[3] = 0x9A;
	buf[4] = 0x1B;
	s->Transfer(buf, 5);
	buf[0] = 0x50;
	buf[1] = 0x53;
	s->Transfer(buf, 2);
	buf[0] = 0x20; // Setup w/o Power mabye important ?
	buf[1] = 0x0D;
	s->Transfer(buf, 2);
	buf[0] = 0x20; // SETUP
	buf[1] = 0x0F; // Power Up etc.
	s->Transfer(buf, 2);
}



int main()
{
	Spi *CS0 = new Spi(0, 1000000, false, false);
	unsigned char buf[100];
	InitChip(CS0);
	int i = 0;
	// init gpio pin for CE
	int fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0)
	{
		printf("Error, could not open /sys/class/gpio/export");
		return -1;
	}
	int bytes = sprintf((char*)buf, "%d", CE_PIN);
	int res = write(fd, buf, bytes);
	if (res < 0)
	{
		printf("Error, could not write to /sys/class/gpio/export");
		return -1;
	}
	close(fd);

	//Init gpio pin direction
	bytes = sprintf((char*)buf, "/sys/class/gpio/gpio%d/direction", CE_PIN);
	fd = open((char*)buf, O_WRONLY);
	if (fd < 0)
	{
		printf("Error opening pin/direction");
		return -1;
	}
	res = write(fd, "out", 3);
	if (res < 0)
	{
		printf("Error writing to pin/direction");
		return -1;
	}
	close(fd);

	while (true)
	{
//		do
//		{
//			usleep(1000);
//			buf[0] = 0xFF; // NOP, Read STATUS
//			CS0->Transfer(buf, 1);
//		} while ((buf[0] & 0x40) == 0); // RX_RD not set
//		buf[0] = 0x27; // Clear Interrupt
//		buf[1] = 0x0E;
//		buf[0] = 0xE2;
//		CS0->Transfer(buf, 1);
//		memset(buf, 0x00, sizeof(buf));
//		buf[0] = 0x61; // Read Payload
//		CS0->Transfer(buf, 17);
//		for (int i = 0; i < 17; i++)
//			printf("%x ", buf[i]);
//		printf("\n");
//		usleep(10000);
		buf[0] = 0x25;
		buf[1] = i;
		CS0->Transfer(buf, 2);
		for (int j = 0; j < 1000; j++)
		{
			buf[0] = 0x09;
			buf[1] = 0x00;
			CS0->Transfer(buf, 2);
			printf("%d: %x %x\n", i, buf[0], buf[1]);
			usleep(1000);
		}
		i++;
		i = i % 128;
	}
	return 0;
}
