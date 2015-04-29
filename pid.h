#ifndef __PID_H__
#define __PID_H__

#include <time.h>

class PID
{
	private:
		double m_dP, m_dI, m_dD, m_dPFactor, m_dIFactor, m_dDFactor, m_dSetpoint, m_dLastError;
	public:
		PID(double dP, double dI, double dD);
		void AddMeasurement(double dMeasurement , double dDeltaTime);
		double GetOutput();
		void SetPFactor(double dP);
		void SetIFactor(double dI);
		void SetDFactor(double dD);
		void SetSetpoint(double dSetpoint);
};

#endif
