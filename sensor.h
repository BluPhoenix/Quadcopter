#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <iostream>
#include <fcntl.h> // open i2c bus
#include <unistd.h>
#include <linux/i2c-dev.h>
#include "vector.h"

#define GYRO_LSB_PER_DEGS 131
#define ACCEL_LSB_PER_G 16384
#define PI 3.14159

class Sensor
{
	private:
		Vector3D m_GyroOffset;
		Vector3D m_AccelOffset;
		int m_iI2CFile;
	public:
		Sensor();
		~Sensor();
		Vector3D GetGyro(); // Returns turn rate in rad / sec
		Vector3D GetAccel();// Returns Acceleration in m/s^2
		void SetGyroOffset(Vector3D GyroOffset) { m_GyroOffset = GyroOffset; }
		void SetAccelOffset(Vector3D AccelOffset) { m_AccelOffset = AccelOffset; }
};

#endif
