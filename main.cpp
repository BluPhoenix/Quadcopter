#include "spi.h"

int main()
{
	Spi *CS0 = new Spi(0, 500000, false, true);
	unsigned char buf[10];
	buf[0] = 0x80;
	CS0->Transfer(buf, 1);
	return 0;
}
