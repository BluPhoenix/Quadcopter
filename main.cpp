#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
int main()
{
/*	int fd = open("/dev/i2c-1", O_RDWR);
	if (fd < 0) std::cout<<"Error opening device"<<std::endl;
	if (ioctl(fd, I2C_SLAVE, 0x68))
	{
		std::cout<<"Error ioctl"<<std::endl;
	}
	i2c_smbus_write_byte_data(fd, 0x6B, 0);
	while (true)
	{
		unsigned char b1 =i2c_smbus_read_byte_data(fd, 0x43);
		unsigned char b2 =i2c_smbus_read_byte_data(fd, 0x44);
		std::cout<<((double)(short)((b1<<8)+b2)/131)<<std::endl;
	}*/

	union { char Bytes[2];
	   	short Value;} test;
	test.Bytes[0] = 0x01;
	test.Bytes[1] = 0x00;
	std::cout<<test.Value<<std::endl;
	return 0;
}
