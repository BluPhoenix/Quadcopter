#include "pid.h"

PID::PID(double dPFactor, double dIFactor, double dDFactor)
	:m_dSetpoint(0), m_dLastError(0), m_dD(0), m_dI(0), m_dP(0), m_dPFactor(dPFactor), m_dIFactor(dIFactor), m_dDFactor(dDFactor)
{
}

void PID::AddMeasurement(double dMeasurement, double dDeltaSeconds)
{
	double dError = m_dSetpoint - dMeasurement;

	m_dP = dError;
	m_dI += dError * dDeltaSeconds;
	m_dD = (dError - m_dLastError) / dDeltaSeconds;
	m_dLastError = dError;
}

double PID::GetOutput()
{
	return m_dP * m_dPFactor + m_dI * m_dIFactor + m_dD * m_dDFactor;
}

void PID::SetDFactor(double dDFactor)
{
	m_dDFactor = dDFactor;
}

void PID::SetIFactor(double dIFactor)
{
	m_dIFactor = dIFactor;
}

void PID::SetPFactor(double dPFactor)
{
	m_dPFactor = dPFactor;
}

void PID::SetSetpoint(double dSetpoint)
{
	m_dSetpoint = dSetpoint;
}


double PID::GetPOutput()
{
	return m_dP * m_dPFactor;
}

double PID::GetIOutput()
{
	return m_dI * m_dIFactor;
}

double PID::GetDOutput()
{
	return m_dD * m_dDFactor;
}

VectorPID::VectorPID(double dPFactor, double dIFactor, double dDFactor)
	:m_LastError(0,0,0), m_D(0,0,0), m_I(0,0,0), m_P(0,0,0), m_dPFactor(dPFactor), m_dIFactor(dIFactor), m_dDFactor(dDFactor), m_Setpoint(0,0,0)
{
}

void VectorPID::AddMeasurement(Vector3D Measurement, double dDeltaSeconds)
{
	Vector3D Error = m_Setpoint - Measurement;

	m_P = Error;
	m_I += Error * dDeltaSeconds;
	m_D = (Error - m_LastError) *(1.0d / dDeltaSeconds);
	m_LastError = Error;
}

Vector3D VectorPID::GetOutput()
{
	return m_P * m_dPFactor + m_I * m_dIFactor + m_D * m_dDFactor;
}

void VectorPID::SetDFactor(double dDFactor)
{
	m_dDFactor = dDFactor;
}

void VectorPID::SetIFactor(double dIFactor)
{
	m_dIFactor = dIFactor;
}

void VectorPID::SetPFactor(double dPFactor)
{
	m_dPFactor = dPFactor;
}

void VectorPID::SetSetpoint(Vector3D Setpoint)
{
	m_Setpoint = Setpoint;
}
