#ifndef __IMU_H__
#define __IMU_H__

#include <iostream>
#include <cmath>

#include "config.h"

#include "vector.h"
#include "pid.h"

class IMU
{
	private:
		Vector3D m_Position, m_Velocity;
		Matrix3x3 m_LocalToGlobal;
		Matrix3x3 m_SensorToLocal;
		VectorPID m_RotCorrectionPID;
	public:
		IMU();
		void SetSensorLocalRotation(Matrix3x3 Rotation);
		void AddGyroMeasurement(Vector3D Gyro, double dDeltaSeconds);
		void AddAccelMeasurement(Vector3D Accel, double dDeltaSeconds);
		double GetRoll();
		double GetPitch();
		double GetYaw();
		Vector3D GetVelocity() { return m_Velocity; }
		Vector3D GetPosition() { return m_Position; }
};

#endif
