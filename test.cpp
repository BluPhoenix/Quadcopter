#include <iostream>

#include <fcntl.h> // Exit on keypress
#include <termios.h>

#include "imu.h"
#include <unistd.h>
#include <time.h>
#include "sensor.h"
#include "pid.h"
#include "config.h"
#include "motorcontrol.h"
#include "fifo/Input.h"


int main()
{
	IMU imu;
	imu.SetSensorLocalRotation(Matrix3x3(0,0,-1,  -1,0,0,  0,1,0));

	Sensor sens;
	timespec ts, lastts;
	clock_gettime(CLOCK_MONOTONIC, &lastts);
	double dTotalTime = 0;

	PID PitchRate(RRC_PITCH_PROPORTIONAL, RRC_PITCH_INTEGRAL, RRC_PITCH_DERIVATE);
	PID RollRate(RRC_ROLL_PROPORTIONAL, RRC_ROLL_INTEGRAL, RRC_ROLL_DERIVATE);
	PID YawRate(RRC_YAW_PROPORTIONAL, RRC_YAW_INTEGRAL, RRC_YAW_DERIVATE);

	PID PitchPos(ARC_PITCH_PROPORTIONAL, ARC_PITCH_INTEGRAL, ARC_PITCH_DERIVATE);
	PID RollPos(ARC_ROLL_PROPORTIONAL, ARC_ROLL_INTEGRAL, ARC_ROLL_DERIVATE);
	PID YawPos(ARC_YAW_PROPORTIONAL, ARC_YAW_INTEGRAL, ARC_YAW_DERIVATE);
	
	double dThrottle = 0;
	double dPitch = 0;
	MotorControl Motors;
	sleep(1);
	Motors.Start();
	sleep(1);
	// Non blocking console for exit command
	//struct termios oldt, newt;
	int oldt;
	oldt = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldt | O_NONBLOCK);


	//Input from CGI script
	Input in;
	while (getchar() == EOF)
	{
		try
		{
			in.Receive();
			dThrottle = in.GetThrottle();
			dPitch = in.GetPitch();
		}
		catch(const char* s)
		{
			std::cout<<s<<std::endl;
			sleep(3);
		}
		std::cout<<dThrottle<<std::endl;
		//std::cout << "\033[2J\033[1;1H"; // Escape code to clear screen.
		clock_gettime(CLOCK_MONOTONIC, &ts);
		double dDeltaTime = ts.tv_sec - lastts.tv_sec + 0.000000001 * (ts.tv_nsec - lastts.tv_nsec);
		dTotalTime += dDeltaTime;
		Vector3D gyr = sens.GetGyro();
		Vector3D accel = sens.GetAccel();
		imu.AddGyroMeasurement(gyr, dDeltaTime);
		imu.AddAccelMeasurement(accel, dDeltaTime);
		lastts = ts;
		//std::cout<<accel;
		//std::cout<<"Yaw: "<<imu.GetYaw()<<"\tPitch: "<<imu.GetPitch()<<"\tRoll: "<<imu.GetRoll()<<std::endl;
		Vector3D FilteredGyr = imu.GetGyro();
		PitchPos.SetSetpoint(dPitch);
		PitchPos.AddMeasurement(imu.GetPitch(), dDeltaTime);
		PitchRate.SetSetpoint(PitchPos.GetOutput());
		PitchRate.AddMeasurement(FilteredGyr.GetY(), dDeltaTime);
		std::cout<<PitchPos.GetOutput()<<std::endl;
		std::cout<<dThrottle - PitchRate.GetOutput()<<std::endl;
		std::cout<<dThrottle + PitchRate.GetOutput()<<std::endl;

		// Motor 1.speed = throttle - PitchRate.GetOutput()
		// Motor 3.speed = throttle + PitchRate.GetOutput()
		//Motors.SetSpeed(1, dThrottle - PitchRate.GetOutput());
		//Motors.SetSpeed(3, dThrottle + PitchRate.GetOutput());
		
		// Logging to Stderr
		// Throttle	Pitch	Roll	Yaw	[Actual P R Y]	[PitchPos-PID]	[RollPos-PID]	[YawPos-PID]
		// [PitchRate-PID]	[RollRate-PID]	[YawRate-PID]	[Motors]
		
		std::cerr<<dThrottle<<"\t"<<dPitch<<"\t0\t0\t";
		
		// Actual Pitch Roll Yaw
		std::cerr<<imu.GetPitch()<<"\t"<<imu.GetRoll()<<"\t"<<imu.GetYaw()<<"\t";
		
		// Pos PIDs
		// [PitchPos-PID]: P-Output	I-Output	D-Output	Output
		std::cerr<<PitchPos.GetPOutput()<<"\t"<<PitchPos.GetIOutput()<<"\t"<<PitchPos.GetDOutput()<<"\t";
		std::cerr<<PitchPos.GetOutput()<<"\t";
		// RollPos-PID
		std::cerr<<RollPos.GetPOutput()<<"\t"<<RollPos.GetIOutput()<<"\t"<<RollPos.GetDOutput()<<"\t";
		std::cerr<<RollPos.GetOutput()<<"\t";
		// YawPos-PID
		std::cerr<<YawPos.GetPOutput()<<"\t"<<YawPos.GetIOutput()<<"\t"<<YawPos.GetDOutput()<<"\t";
		std::cerr<<YawPos.GetOutput()<<"\t";

		// Rate PIDs
		// [PitchRate-PID]: P-Output	I-Output	D-Output	Output
		std::cerr<<PitchRate.GetPOutput()<<"\t"<<PitchRate.GetIOutput()<<"\t"<<PitchRate.GetDOutput()<<"\t";
		std::cerr<<PitchRate.GetOutput()<<"\t";
		// RollRate-PID
		std::cerr<<RollRate.GetPOutput()<<"\t"<<RollRate.GetIOutput()<<"\t"<<RollRate.GetDOutput()<<"\t";
		std::cerr<<RollRate.GetOutput()<<"\t";
		// YawRate-PID
		std::cerr<<YawRate.GetPOutput()<<"\t"<<YawRate.GetIOutput()<<"\t"<<YawRate.GetDOutput()<<"\t";
		std::cerr<<YawRate.GetOutput()<<"\t";

		// [Motors]: Motor1	Motor2	Motor3	Motor4
		std::cerr<<dThrottle - PitchRate.GetOutput()<<"\t0\t"<<dThrottle + PitchRate.GetOutput();
		std::cerr<<std::endl;
		usleep(20000);
	}
	Motors.Stop();
	return 0;
}
