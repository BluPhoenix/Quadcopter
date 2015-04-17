#include "imu.h"

IMU::IMU()
{
	m_iI2CFile = open("/" /* I2C Device name goes here */, O_RDWR);
	// To do initialization as in the datasheet
	
}

IMU::~IMU()
{
	close(m_iI2CFile);
}
