#include "spi.h"
#include <unistd.h>
int main()
{
	Spi *CS0 = new Spi(0, 500000, false, true);
	unsigned char buf[10];
while (true)
{
	buf[0] = 0x01;
	buf[1] = 100;
	CS0->Transfer(buf, 2);
	sleep(5);
	buf[0] = 0x01;
	buf[1] = 200;
	CS0->Transfer(buf, 2);
	sleep(5);
}
	return 0;
}
