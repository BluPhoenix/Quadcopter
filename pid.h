#ifndef __PID_H__
#define __PID_H__

#include "vector.h"

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

class VectorPID
{
	private:
		Vector3D m_P, m_I, m_D, m_Setpoint, m_LastError;
		double m_dPFactor, m_dIFactor, m_dDFactor;
	public:
		VectorPID(double dP, double dI, double dD);
		void AddMeasurement(Vector3D Measurement , double dDeltaTime);
		Vector3D GetOutput();
		void SetPFactor(double dP);
		void SetIFactor(double dI);
		void SetDFactor(double dD);
		void SetSetpoint(Vector3D Setpoint);
};
#endif
