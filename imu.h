#ifndef __IMU_H__
#define __IMU_H__

#include <iostream>
#include "vector.h"
#include <time.h>
#include <math.h>

class IMU
{
	private:
		struct timespec m_GyroTS, m_AccelTS;
		Vector3D m_Position, m_Velocity;
		Matrix3x3 m_GlobalToLocal;
		Matrix3x3 m_SensorToLocal;
	public:
		IMU();
		void SetSensorLocalRotation(Matrix3x3 Rotation);
		void AddGyroMeasurement(Vector3D Gyro);
		void AddAccelMeasurement(Vector3D Accel);
		double GetRoll();
		double GetPitch();
		double GetYaw();
		Vector3D GetVelocity() { return m_Velocity; }
		Vector3D GetPosition() { return m_Position; }
};

#endif
