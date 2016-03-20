#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h> // mkfifo
#include <sys/stat.h>


#define YAW_FACTOR 1
#define PITCH_FACTOR 1
#define ROLL_FACTOR 1


class InputParser
{
	public:
		struct Coord
		{
			union {int X; char byX[4]; };
			union {int Y; char byY[4]; };
			union {int Z; char byZ[4]; };
		};

		InputParser();
		void Reset();

		Coord GetLastCoord();
		unsigned int GetLastThrottle();
		
		bool PutChar(char Input);
	private:
		enum State {IDLE, COORDSX1, COORDSX2, COORDSX3, COORDSX4, COORDSY1, COORDSY2, COORDSY3, COORDSY4,
								COORDSZ1, COORDSZ2, COORDSZ3, COORDSZ4, THROTTLE1, THROTTLE2, THROTTLE3, THROTTLE4};
		State m_CurrentState;
		unsigned int m_uiLastThrottle;
		Coord m_LastCoord;
		union {unsigned int m_uiCurThrottle; char m_byThrottle[4]; };
		Coord m_CurCoord;
};

class Input
{
	private:
		int m_FD;
		InputParser m_Parser;
	public:
		Input();
		~Input();
		void Receive();
		float GetPitch();
		float GetRoll();
		float GetYaw();
		float GetThrottle();
};
