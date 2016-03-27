#ifndef __CONFIG_H__
#define __CONFIG_H__

#define PI 3.14159265359

// Sensor Settings
#define GYRO_LSB_PER_DEGS 131
#define ACCEL_LSB_PER_G 16384
#define ACCEL_OFFSET 0, 0, 0
#define GYRO_OFFSET -0.0160916, -0.0646219, 0.0111878

#define IMU_CORRECTION_PROPORTIONAL 0.5
#define IMU_CORRECTION_INTEGRAL		0.01
#define IMU_CORRECTION_DERIVATE 	0


// Rotation Rate Control PIDs

#define RRC_PITCH_PROPORTIONAL  15
#define RRC_PITCH_INTEGRAL		0
#define RRC_PITCH_DERIVATE		0

#define RRC_ROLL_PROPORTIONAL	0
#define RRC_ROLL_INTEGRAL		0
#define RRC_ROLL_DERIVATE		0

#define RRC_YAW_PROPORTIONAL	0
#define RRC_YAW_INTEGRAL		0
#define RRC_YAW_DERIVATE		0

// Absolute Rotation Control PIDs

#define ARC_PITCH_PROPORTIONAL	0
#define ARC_PITCH_INTEGRAL		0
#define ARC_PITCH_DERIVATE		0

#define ARC_ROLL_PROPORTIONAL	0
#define ARC_ROLL_INTEGRAL		0
#define ARC_ROLL_DERIVATE		0

#define ARC_YAW_PROPORTIONAL	0
#define ARC_YAW_INTEGRAL		0
#define ARC_YAW_DERIVATE		0


// Motors start to turn at 20%

#define MOTOR_SPEED_BIAS 20

#endif //__CONFIG_H__
