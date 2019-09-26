#include "main.h"
#include "common.h"
using namespace okapi;

/**
 * Chassis and global variables
 */

// Modifier controller sensitivity
const float CONT_X_MODIFIER = 0.3;
const float CONT_Y_MODIFIER = 0.5;

// Motor ports
const int DRIVE_MOTOR_LEFT_F = 2;
const int DRIVE_MOTOR_LEFT_B = 11;
const int DRIVE_MOTOR_RIGHT_F = 3;
const int DRIVE_MOTOR_RIGHT_B = 12;

// Chassis measurements
const QLength WHEEL_DIAMETER = 4_in;
const QLength CHASSIS_WIDTH = 12.5_in;

// Chassis
ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
  {-DRIVE_MOTOR_LEFT_F, -DRIVE_MOTOR_LEFT_B},  // Left motors
	{DRIVE_MOTOR_RIGHT_F, DRIVE_MOTOR_RIGHT_B},  // Right motors
  AbstractMotor::gearset::green,  // Torque gearset
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);
