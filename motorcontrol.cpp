#include "motorcontrol.h"

MotorControl::MotorControl()
{
	for (int i = 0; i < 4; i++)
		m_dMotorSpeeds[i] = 0;
	
	// CS=0; Clk=500kHz; CSLine=High; PulseCS=true; Clock=ActiveHigh;
	m_pSpidev = new Spi(0, 500000, true, true, false);
	unsigned char buf[2];

	// Bytes have to be inverted due to Hardware inverter used as logic level converter
	buf[0] = 0xFF ^ 1; // Motor 1
	buf[1] = 0xFF ^ 100; // 100 -> 1ms -> Motor Off (2ms = Full Throttle)
	m_pSpidev->Transfer(buf, 2);
	buf[0] = 0xFF ^ 2; // Motor 2
	buf[1] = 0xFF ^ 100; // 100 -> 1ms -> Motor Off (2ms = Full Throttle)
	m_pSpidev->Transfer(buf, 2);
	buf[0] = 0xFF ^ 3; // Motor 3
	buf[1] = 0xFF ^ 100; // 100 -> 1ms -> Motor Off (2ms = Full Throttle)
	m_pSpidev->Transfer(buf, 2);
	buf[0] = 0xFF ^ 4; // Motor 4
	buf[1] = 0xFF ^ 100; // 100 -> 1ms -> Motor Off (2ms = Full Throttle)
	m_pSpidev->Transfer(buf, 2);
}

MotorControl::~MotorControl()
{
	delete m_pSpidev;
}

void MotorControl::SetSpeed(unsigned int uiMotor, double dSpeed)
{
	if ((uiMotor < 1) || (uiMotor > 4))
	{
		std::cout<<"Error Invalid Motor ID"<<std::endl;
		return;
	}
	if (dSpeed < 0)
	{
		std::cout<<"Warning: Negative Speed"<<std::endl;
		dSpeed = 0;
	}
	if (dSpeed > 1)
	{
		std::cout<<"Warning: Speed Exceeding Range"<<std::endl;
		dSpeed = 1;
	}
	if (dSpeed == 1)
	{
		std::cout<<"Warning: Full Throttle in Motor "<<uiMotor<<std::endl;
	}
	unsigned char buf[2];
	buf[0] = uiMotor ^ 0xFF;
	buf[1] = 100 + 100 * dSpeed;
	buf[1] ^= 0xFF;
	m_pSpidev->Transfer(buf, 2);
	m_dMotorSpeeds[uiMotor - 1] = dSpeed;
}

double MotorControl::GetSpeed(unsigned int uiMotor)
{
	if ((uiMotor < 1) || (uiMotor > 4))
	{
		std::cout<<"Error: Invalid Motor ID"<<std::endl;
		return 0;
	}
	return m_dMotorSpeeds[uiMotor -1];
}

void MotorControl::AddSpeed(unsigned int uiMotor, double dDeltaSpeed)
{
	if ((uiMotor < 1) || (uiMotor > 4))
	{
		std::cout<<"Error: Invalid Motor ID"<<std::endl;
		return;
	}
	m_dMotorSpeeds[uiMotor - 1] += dDeltaSpeed;
	if (m_dMotorSpeeds[uiMotor - 1] < 0)
	{
		m_dMotorSpeeds[uiMotor - 1] = 0;
		std::cout<<"Warning: Motor Turned off in AddSeed(unsigned int, double);"<<std::endl;
	}
	if (m_dMotorSpeeds[uiMotor - 1] > 1)
	{
		m_dMotorSpeeds[uiMotor - 1] = 1;
		std::cout<<"Warning: Motor Ful Throttle in AddSpeed(unsigned int, double);"<<std::endl;
	}
	unsigned char buf[2];
	buf[0] = uiMotor ^ 0xFF;
	buf[1] = 0xFF ^ (int)(100 + 100 * m_dMotorSpeeds[uiMotor - 1]);
	m_pSpidev->Transfer(buf, 2);
}
