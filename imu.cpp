#include "imu.h"

IMU::IMU()
:m_RotCorrectionPID(IMU_CORRECTION_PROPORTIONAL,IMU_CORRECTION_INTEGRAL,IMU_CORRECTION_DERIVATE)
{
	int i=0,j=0;
	m_SensorToLocal *= 0;
	for (i = 0; i < 3; i++)
	{
		m_SensorToLocal.SetCell(i,j,1);
		m_LocalToGlobal.SetCell(i,j,1);
		j++;
	}
	for (i = 0; i < GYRO_SMOOTHING; i++)
	{
		m_GyroList.push_front(Vector3D(0,0,0));
	}
}

void IMU::SetSensorLocalRotation(Matrix3x3 Rotation)
{
	m_SensorToLocal = Rotation;
}

void IMU::AddGyroMeasurement(Vector3D Gyro, double dDeltaSeconds)
{


	//Use a PI to correct the Gyro drift
	Vector3D LocalGyro = (m_SensorToLocal * Gyro - m_RotCorrectionPID.GetOutput());

	// Add new Vector to Smooting queue
	m_GyroList.pop_back();
	m_GyroList.push_front(LocalGyro);

	LocalGyro = LocalGyro * dDeltaSeconds;

	Matrix3x3 CombinedCross(1, LocalGyro.GetZ(),-1 * LocalGyro.GetY(),
	 						-1 * LocalGyro.GetZ(), 1, LocalGyro.GetX(),
							LocalGyro.GetY(), -1 * LocalGyro.GetX(), 1);   
	m_LocalToGlobal = CombinedCross * m_LocalToGlobal;
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
	Vector3D LocalAccel = m_SensorToLocal * Accel * dDeltaSeconds;
	LocalAccel.Normalize();
	Vector3D GlobalZ = m_LocalToGlobal * Vector3D(0,0,1);
	m_RotCorrectionPID.AddMeasurement(Vector3D::Cross(LocalAccel, GlobalZ), dDeltaSeconds);
}

// Positive Roll = X-Axis pointing down
double IMU::GetRoll()
{	
	return asin((m_LocalToGlobal * Vector3D(0,1,0)) * Vector3D(0,0,1));
}

// Positive Pitch = Y-Axis pointing down
double IMU::GetPitch()
{
	return asin((m_LocalToGlobal * Vector3D(1,0,0)) * Vector3D(0,0,1));
}

// Positive Yaw = X-Axis pointing Left
double IMU::GetYaw()
{
	Vector3D GlobalDirection = m_LocalToGlobal * Vector3D(1,0,0);
	GlobalDirection.SetZ(0);
	GlobalDirection.Normalize();
	if (Vector3D(1,0,0) * GlobalDirection > 0)
		return asin(Vector3D::Cross(GlobalDirection, Vector3D(1,0,0)) * Vector3D(0,0,1));
	double temp = PI - asin(Vector3D::Cross(GlobalDirection, Vector3D(1,0,0)) * Vector3D(0,0,1));
	if (temp > PI) temp -= 2 * PI;
	return temp;
}

Vector3D IMU::GetGyro()
{
	Vector3D ret(0,0,0);
	for (std::list<Vector3D>::iterator it = m_GyroList.begin(); it != m_GyroList.end(); it++)
	{
		ret += *it;
	}
	return ret * (1.0d / GYRO_SMOOTHING);
}
