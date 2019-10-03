#include "main.h"
using namespace okapi;

/**
 * Chassis and global variables
 */

// Modifier controller sensitivity
extern const float CONT_X_MODIFIER;
extern const float CONT_Y_MODIFIER;

// Motor ports
extern const int DRIVE_MOTOR_LEFT_F;
extern const int DRIVE_MOTOR_LEFT_B;
extern const int DRIVE_MOTOR_RIGHT_F;
extern const int DRIVE_MOTOR_RIGHT_B;

// Chassis measurements
extern const QLength WHEEL_DIAMETER;
extern const QLength CHASSIS_WIDTH;

// Gear ratio
extern const AbstractMotor::GearsetRatioPair GEAR_RATIO;

// Chassis
extern ChassisControllerIntegrated chassis;
