#ifndef __MOTORCONTROL_H__
#define __MOTORCONTROL_H__

#include "spi.h"
#include <iostream>
#include "config.h"

class MotorControl
{
	private:
		bool m_bStarted;
		double m_dMotorSpeeds[4];
		Spi *m_pSpidev;
	public:
		MotorControl();
		~MotorControl();
		void SetSpeed(unsigned int uiMotor, double dSpeed);
		double GetSpeed(unsigned int uiMotor);
		void Start();
		void Stop();
};


#endif
