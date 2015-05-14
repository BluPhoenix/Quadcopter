#include "sensor.h"

Sensor::Sensor()
	: m_GyroOffset(GYRO_OFFSET), m_AccelOffset(ACCEL_OFFSET)
{
	m_iI2CFile = open("/dev/i2c-1", O_RDWR);
	if (m_iI2CFile < 0)
	{
		std::cout<<"Error opening I2C Device"<<std::endl;
	}
	ioctl(m_iI2CFile, I2C_SLAVE, 0x68);
	// To do initialization as in the datasheet
	i2c_smbus_write_byte_data(m_iI2CFile, 0x6B, 0); // Power up
}

Sensor::~Sensor()
{
	close(m_iI2CFile);
}

Vector3D Sensor::GetGyro()
{
	Vector3D ret;
	union { char Bytes[2]; short iValue; } Data;
	Data.Bytes[0] = i2c_smbus_read_byte_data(m_iI2CFile, 0x44);
	Data.Bytes[1] = i2c_smbus_read_byte_data(m_iI2CFile, 0x43);
	ret.SetX((PI / 180 / GYRO_LSB_PER_DEGS) * Data.iValue);
	Data.Bytes[0] = i2c_smbus_read_byte_data(m_iI2CFile, 0x46);
	Data.Bytes[1] = i2c_smbus_read_byte_data(m_iI2CFile, 0x45);
	ret.SetY((PI / 180 / GYRO_LSB_PER_DEGS) * Data.iValue);
	Data.Bytes[0] = i2c_smbus_read_byte_data(m_iI2CFile, 0x48);
	Data.Bytes[1] = i2c_smbus_read_byte_data(m_iI2CFile, 0x47);
	ret.SetZ((PI / 180 / GYRO_LSB_PER_DEGS) * Data.iValue);
	ret += m_GyroOffset;
	return ret;
}

Vector3D Sensor::GetAccel()
{
	Vector3D ret;
	union { char Bytes[2]; short iValue; } Data;
	Data.Bytes[0] = i2c_smbus_read_byte_data(m_iI2CFile, 0x3C);
	Data.Bytes[1] = i2c_smbus_read_byte_data(m_iI2CFile, 0x3B);
	ret.SetX((1.0d/ ACCEL_LSB_PER_G) * Data.iValue);
	Data.Bytes[0] = i2c_smbus_read_byte_data(m_iI2CFile, 0x3E);
	Data.Bytes[1] = i2c_smbus_read_byte_data(m_iI2CFile, 0x3D);
	ret.SetY((1.0d / ACCEL_LSB_PER_G) * Data.iValue);
	Data.Bytes[0] = i2c_smbus_read_byte_data(m_iI2CFile, 0x40);
	Data.Bytes[1] = i2c_smbus_read_byte_data(m_iI2CFile, 0x3F);
	ret.SetZ((1.0d / ACCEL_LSB_PER_G) * Data.iValue);
	ret += m_AccelOffset;
	return ret;
}
