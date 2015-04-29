#include "pid.h"

PID::PID(double dPFactor, double dIFactor, double dDFactor)
	:m_dLastError(0), m_dD(0), m_dI(0), m_dP(0), m_dPFactor(dPFactor), m_dIFactor(dIFactor), m_dDFactor(dDFactor)
{
}

void PID::AddMeasurement(double dMeasurement, double dDeltaSeconds)
{
	double dError = dMeasurement - m_dSetpoint;

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
