#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <errno.h>
void writeCoord(int fd, int X, int Y, int Z)
{
	write(fd, "c", 1);
	write(fd, (char*)&X, sizeof(X));
	write(fd, (char*)&Y, sizeof(Y));
	write(fd, (char*)&Z, sizeof(Z));
}

void writeThrottle(int fd, unsigned int throttle)
{
	std::cout<<write(fd, "t", 1)<<std::endl;
	std::cout<<write(fd, (char*)&throttle, sizeof(throttle));
}

int main()
{
	std::cout<< "Content-Type: text/html\n\n";


	char type;
	std::cin>>type;
	if (type == 'c')
	{
		int X,Y,Z;
		std::cin>>X;
		std::cin>>Y;
		std::cin>>Z;
		int fd = open("/tmp/ctl_fifo", O_WRONLY);
		std::cout<<X<<"\t"<<Y<<"\t"<<Z<<std::endl;
		writeCoord(fd, X, Y, Z);
		close(fd);
	}
	else
	{
		int throttle;
		std::cin>>throttle;
		int fd = open("/tmp/ctl_fifo", O_WRONLY);
		std::cout<<fd<<std::endl;
		if (fd == -1)
			std::cout<<errno<<std::endl;
		writeThrottle(fd, throttle);
		close(fd);
	}
	return 0;
}
