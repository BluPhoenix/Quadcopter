#include "spi.h"
#include <unistd.h>
int main()
{
	Spi *CS0 = new Spi(0, 500000, true, true, false);
	unsigned char buf[10];
while (true)
{
	buf[0] = 0xFE;
	buf[1] = 100 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
	buf[0] = 0x01 ^ 0xFF;
	buf[1] = 150 ^ 0xFF;
	CS0->Transfer(buf, 2);
	sleep(5);
}
	return 0;
}
