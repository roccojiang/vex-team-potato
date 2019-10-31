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
const int DRIVE_MOTOR_LEFT_F = 5;
const int DRIVE_MOTOR_LEFT_B = 15;
const int DRIVE_MOTOR_RIGHT_F = 6;
const int DRIVE_MOTOR_RIGHT_B = 16;

const int INTAKE_MOTOR_LEFT_P = 11;
const int INTAKE_MOTOR_RIGHT_P = 20;

// Motors
Motor INTAKE_MOTOR_LEFT(11);
Motor INTAKE_MOTOR_RIGHT(-20);

// Motor groups
MotorGroup INTAKE_MOTORS({INTAKE_MOTOR_LEFT, INTAKE_MOTOR_RIGHT});

// Chassis measurements
const QLength WHEEL_DIAMETER = 4_in;
const QLength CHASSIS_WIDTH = 13.5_in;  // Track width

// Gear ratio
const AbstractMotor::GearsetRatioPair GEAR_RATIO = AbstractMotor::gearset::green * (36.0/84.0);

// Chassis
ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
  {-DRIVE_MOTOR_LEFT_F, -DRIVE_MOTOR_LEFT_B},  // Left motors
	{DRIVE_MOTOR_RIGHT_F, DRIVE_MOTOR_RIGHT_B},  // Right motors
  GEAR_RATIO,  // Motor gearset multiplied by external physical gear ratio
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);
