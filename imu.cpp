#include "imu.h"

IMU::IMU()
{
	int i=0,j=0;
	m_SensorToLocal *= 0;
	for (i = 0; i < 3; i++)
	{
		m_SensorToLocal.SetCell(i,j,1);
		m_LocalToGlobal.SetCell(i,j,1);
		j++;
	}
}

void IMU::SetSensorLocalRotation(Matrix3x3 Rotation)
{
	m_SensorToLocal = Rotation;
}

void IMU::AddGyroMeasurement(Vector3D Gyro, double dDeltaSeconds)
{
	Vector3D GlobalGyro = m_LocalToGlobal * m_SensorToLocal * Gyro * dDeltaSeconds;
	m_LocalToGlobal = m_LocalToGlobal * Matrix3x3(1, -1 * GlobalGyro.GetZ(), GlobalGyro.GetY(),
														GlobalGyro.GetZ(), 1, -1 * GlobalGyro.GetX(),
														-1 * GlobalGyro.GetY(), GlobalGyro.GetX(), 1);
	m_LocalToGlobal.Renormalization();
	std::cout<<"Delta Seconds: "<<dDeltaSeconds<<std::endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout<<m_LocalToGlobal.GetCell(i,j)<<" ";
		}
		std::cout<<std::endl;
	}
}

void IMU::AddAccelMeasurement(Vector3D Accel, double dDeltaSeconds)
{
	Vector3D GlobalAccel = m_SensorToLocal * m_LocalToGlobal * Accel * dDeltaSeconds;
	m_Velocity += GlobalAccel;
	m_Position += m_Velocity * dDeltaSeconds;
}

double IMU::GetRoll()
{
	return asin((m_LocalToGlobal * Vector3D(0,1,0)) * Vector3D(0,0,1));
}

double IMU::GetPitch()
{
	return asin((m_LocalToGlobal * Vector3D(1,0,0)) * Vector3D(0,0,1));
}

double IMU::GetYaw()
{
	Vector3D GlobalDirection = m_LocalToGlobal * Vector3D(1,0,0);
	GlobalDirection.SetZ(0);
	GlobalDirection.Normalize();
	return asin(Vector3D::Cross(GlobalDirection, Vector3D(1,0,0)).GetLength());
}
