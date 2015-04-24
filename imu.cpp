#include "imu.h"

IMU::IMU()
{
	clock_gettime(CLOCK_MONOTONIC, &m_GyroTS);
	clock_gettime(CLOCK_MONOTONIC, &m_AccelTS);
	int i=0,j=0;
	m_SensorToLocal *= 0;
	for (i = 0; i < 3; i++)
	{
		m_SensorToLocal.SetCell(i,j,1);
		m_GlobalToLocal.SetCell(i,j,1);
		j++;
	}
}

void IMU::SetSensorLocalRotation(Matrix3x3 Rotation)
{
	m_SensorToLocal = Rotation;
}

void IMU::AddGyroMeasurement(Vector3D Gyro)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	double dDeltaSeconds = (double)ts.tv_sec - (double)m_GyroTS.tv_sec + ((double)ts.tv_nsec - (double)m_GyroTS.tv_nsec) * 0.000000001;
	m_GyroTS = ts;
	Vector3D GlobalGyro = m_SensorToLocal * Gyro * dDeltaSeconds;
	m_GlobalToLocal = m_GlobalToLocal * Matrix3x3(1, -1 * GlobalGyro.GetZ(), GlobalGyro.GetY(),
														GlobalGyro.GetZ(), 1, -1 * GlobalGyro.GetX(),
														-1 * GlobalGyro.GetY(), GlobalGyro.GetX(), 1);
	m_GlobalToLocal.Renormalization();
	std::cout<<"Delta Seconds: "<<dDeltaSeconds<<std::endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout<<m_GlobalToLocal.GetCell(i,j)<<" ";
		}
		std::cout<<std::endl;
	}
}

void IMU::AddAccelMeasurement(Vector3D Accel)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	double dDeltaSeconds = (double)ts.tv_sec - (double)m_AccelTS.tv_sec + ((double)ts.tv_nsec - (double)m_AccelTS.tv_nsec) * 0.000000001;
	m_AccelTS = ts;

	Vector3D GlobalAccel = m_SensorToLocal * m_GlobalToLocal * Accel * dDeltaSeconds;
	m_Velocity += GlobalAccel;
	m_Position += m_Velocity * dDeltaSeconds;
}

double IMU::GetRoll()
{
	return asin((m_GlobalToLocal * Vector3D(0,1,0)) * Vector3D(0,0,1));
}

double IMU::GetPitch()
{
	return asin((m_GlobalToLocal * Vector3D(1,0,0)) * Vector3D(0,0,1));
}

double IMU::GetYaw()
{
	Vector3D GlobalDirection = m_GlobalToLocal * Vector3D(1,0,0);
	GlobalDirection.SetZ(0);
	GlobalDirection.Normalize();
	return asin(Vector3D::Cross(GlobalDirection, Vector3D(1,0,0)).GetLength());
}
