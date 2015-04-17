#ifndef __IMU_H__
#define __IMU_H__

#include <fcntl.h> // open i2c bus
#include <unistd.h>

class IMU
{
	private:
		int m_iI2CFile;
	public:
		IMU();
		~IMU();
};

#endif
