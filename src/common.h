#include "main.h"
using namespace okapi;

/**
 * Controller initialisation
 */

// Controllers
extern Controller master;
extern Controller partner;
extern ControllerButton autonomous_button;
extern ControllerButton intake_in_button;
extern ControllerButton intake_out_slow_button;
extern ControllerButton intake_out_button;
extern ControllerButton lift_up_button;
extern ControllerButton lift_down_button;

/**
 * Chassis and global variables
 */

// Modifier controller sensitivity
extern const float CONT_X_MODIFIER;
extern const float CONT_Y_MODIFIER;

// Motor ports
extern const int DRIVE_MOTOR_LEFT;
extern const int DRIVE_MOTOR_RIGHT;

extern const int INTAKE_MOTOR_LEFT_P;
extern const int INTAKE_MOTOR_RIGHT_P;

extern const int LIFT_MOTOR_LEFT_P;
extern const int LIFT_MOTOR_RIGHT_P;

// Motors
extern Motor INTAKE_MOTOR_LEFT;
extern Motor INTAKE_MOTOR_RIGHT;

extern Motor LIFT_MOTOR_LEFT;
extern Motor LIFT_MOTOR_RIGHT;

// Motor groups
extern MotorGroup INTAKE_MOTORS;
extern MotorGroup LIFT_MOTORS;

// Chassis measurements
extern const QLength WHEEL_DIAMETER;
extern const QLength CHASSIS_WIDTH;
extern const QLength CHASSIS_LENGTH;

// Gear ratio
extern const AbstractMotor::GearsetRatioPair GEAR_RATIO;

// Chassis
extern ChassisControllerIntegrated chassis;

// Async controller for motion profile
extern AsyncMotionProfileController profile_controller;

// Async controller for intake
extern AsyncVelIntegratedController intake_controller;

// Async controller for lift
extern AsyncPosIntegratedController lift_controller;
extern const int NUM_HEIGHTS;
extern const int START_HEIGHT;
extern const int HEIGHTS[5];
