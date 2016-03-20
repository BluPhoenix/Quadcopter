#include "Input.h"
#include <errno.h>

InputParser::InputParser()
{
	m_CurrentState = IDLE;
	m_LastCoord = (InputParser::Coord){ {0}, {0}, {0} };
	m_uiLastThrottle = 0;
}

InputParser::Coord InputParser::GetLastCoord()
{
	return m_LastCoord;
}

unsigned int InputParser::GetLastThrottle()
{
	return m_uiLastThrottle;
}

bool InputParser::PutChar(char Input)
{
	switch(m_CurrentState)
	{
		case IDLE:
			switch(Input)
			{
				case 'c':
					m_CurrentState = COORDSX1;
					return true;
				case 't':
					m_CurrentState = THROTTLE1;
					return true;
				default:
					return false;
			}
			break;
		case COORDSX1:
			m_CurCoord.byX[0] = Input;
			m_CurrentState = COORDSX2;
			return true;
		case COORDSX2:
			m_CurCoord.byX[1] = Input;
			m_CurrentState = COORDSX3;
			return true;
		case COORDSX3:
			m_CurCoord.byX[2] = Input;
			m_CurrentState = COORDSX4;
			return true;
		case COORDSX4:
			m_CurCoord.byX[3] = Input;
			m_CurrentState = COORDSY1;
			return true;
		case COORDSY1:
			m_CurCoord.byY[0] = Input;
			m_CurrentState = COORDSY2;
			return true;
		case COORDSY2:
			m_CurCoord.byY[1] = Input;
			m_CurrentState = COORDSY3;
			return true;
		case COORDSY3:
			m_CurCoord.byY[2] = Input;
			m_CurrentState = COORDSY4;
			return true;
		case COORDSY4:
			m_CurCoord.byY[3] = Input;
			m_CurrentState = COORDSZ1;
			return true;
		case COORDSZ1:
			m_CurCoord.byZ[0] = Input;
			m_CurrentState = COORDSZ2;
			return true;
		case COORDSZ2:
			m_CurCoord.byZ[1] = Input;
			m_CurrentState = COORDSZ3;
			return true;
		case COORDSZ3:
			m_CurCoord.byZ[2] = Input;
			m_CurrentState = COORDSZ4;
			return true;
		case COORDSZ4:
			m_CurCoord.byZ[3] = Input;
			m_CurrentState = IDLE;
			m_LastCoord = m_CurCoord;
			return true;
		case THROTTLE1:
			m_byThrottle[0] = Input;
			m_CurrentState = THROTTLE2;
			return true;
		case THROTTLE2:
			m_byThrottle[1] = Input;
			m_CurrentState = THROTTLE3;
			return true;
		case THROTTLE3:
			m_byThrottle[2] = Input;
			m_CurrentState = THROTTLE4;
			return true;
		case THROTTLE4:
			m_byThrottle[3] = Input;
			m_CurrentState = IDLE;
			m_uiLastThrottle = m_uiCurThrottle;
			return true;
	}
	return false;
}


Input::Input()
{
	unlink("/tmp/ctl_fifo");
	umask(0);
	if (mkfifo("/tmp/ctl_fifo", 0666) == -1)
	{
		throw "Could not create FIFO";
	}
	m_FD = open("/tmp/ctl_fifo", O_RDONLY | O_NONBLOCK);
	if (m_FD < 0)
	{
		throw "Could not open FIFO";
	}
	umask(022);
}

Input::~Input()
{
	close(m_FD);
	unlink("/tmp/ctl_fifo");
}

void Input::Receive()
{
	char buf[100];
	ssize_t recv;
	while ((recv = read(m_FD, buf, sizeof(buf))) > 0)
	{
		for (ssize_t i = 0; i < recv; i++)
		{
			m_Parser.PutChar(buf[i]);
		}
	}
	if (recv < 0)
	{
		if (errno != EAGAIN) throw "Error While Reading";
	}
}

float Input::GetPitch()
{
	return m_Parser.GetLastCoord().X * PITCH_FACTOR;
}

float Input::GetRoll()
{
	return m_Parser.GetLastCoord().Y * ROLL_FACTOR;
}

float Input::GetYaw()
{
	return m_Parser.GetLastCoord().Z * YAW_FACTOR;
}

float Input::GetThrottle()
{
	if (m_Parser.GetLastThrottle() > 100) return 100;
	return m_Parser.GetLastThrottle();
}
