#include "spi.h"
#include <unistd.h>
int main()
{
	Spi *CS0 = new Spi(0, 500000, true, true, false);
	unsigned char buf[10];
while (true)
{
	// The control board has a hardware inverter so the clock polarity, the cs line 
	// and the data lines have to be inverted
	
	buf[0] = 0x01 ^ 0xFF;
	buf[1] = 150 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
	buf[0] = 0x01 ^ 0xFF;
	buf[1] = 100 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
	buf[0] = 0x02 ^ 0xFF;
	buf[1] = 150 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
	buf[0] = 0x02 ^ 0xFF;
	buf[1] = 100 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
	buf[0] = 0x03 ^ 0xFF;
	buf[1] = 150 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
	buf[0] = 0x03 ^ 0xFF;
	buf[1] = 100 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
	buf[0] = 0x04 ^ 0xFF;
	buf[1] = 150 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
	buf[0] = 0x04 ^ 0xFF;
	buf[1] = 100 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
}
	return 0;
}
