#include "main.h"
#include "common.h"
using namespace okapi;

/**
 * Controller initialisation
 */

// Controllers
Controller master(ControllerId::master);
Controller partner(ControllerId::partner);
ControllerButton autonomous_button(ControllerId::partner, ControllerDigital::Y);
ControllerButton intake_in_button(ControllerId::partner, ControllerDigital::A);
ControllerButton intake_out_slow_button(ControllerId::partner, ControllerDigital::B);
ControllerButton intake_out_button(ControllerId::partner, ControllerDigital::X);
ControllerButton lift_up_button(ControllerId::partner, ControllerDigital::R1);
ControllerButton lift_down_button(ControllerId::partner, ControllerDigital::L1);

/**
 * Chassis and global variables
 */

// Modifier controller sensitivity
const float CONT_X_MODIFIER = 1.0;
const float CONT_Y_MODIFIER = 1.0;

// Motor ports
const int DRIVE_MOTOR_LEFT = 15;
const int DRIVE_MOTOR_RIGHT = 16;

const int INTAKE_MOTOR_LEFT_P = 1;
const int INTAKE_MOTOR_RIGHT_P = 10;

const int LIFT_MOTOR_LEFT_P = 14;
const int LIFT_MOTOR_RIGHT_P = 17;

const int PUSH_MOTOR_P = 14;

// Motors
Motor INTAKE_MOTOR_LEFT(INTAKE_MOTOR_LEFT_P);
Motor INTAKE_MOTOR_RIGHT(INTAKE_MOTOR_RIGHT_P);

Motor LIFT_MOTOR_LEFT(LIFT_MOTOR_LEFT_P);
Motor LIFT_MOTOR_RIGHT(LIFT_MOTOR_RIGHT_P);

Motor PUSH_MOTOR(14);

// Motor groups
MotorGroup INTAKE_MOTORS({1, -10});
MotorGroup LIFT_MOTORS({14, -17});

// Chassis measurements
const QLength WHEEL_DIAMETER = 4_in;
const QLength CHASSIS_WIDTH = 15_in;  // Track width - need to fix
const QLength CHASSIS_LENGTH = 18_in;

// Gear ratio
const AbstractMotor::GearsetRatioPair GEAR_RATIO = AbstractMotor::gearset::green * (18.0/12.0);

// Chassis
ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
  DRIVE_MOTOR_LEFT,
	-DRIVE_MOTOR_RIGHT,
  GEAR_RATIO,  // Motor gearset multiplied by external physical gear ratio
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);

// Async controller for motion profile
AsyncMotionProfileController profile_controller = AsyncControllerFactory::motionProfile(
  1.0,  // Max linear velocity, m/s
  2.0,  // Max linear acceleration, m/s^2
  10.0,  // Max linear jerk, m/s^3
  chassis  // Chassis controller
);

// Async controller for intake
AsyncVelIntegratedController intake_controller = AsyncControllerFactory::velIntegrated(INTAKE_MOTORS);

// Async controller for lift
AsyncPosIntegratedController lift_controller = AsyncControllerFactory::posIntegrated(LIFT_MOTORS);
const int NUM_HEIGHTS = 5;
const int START_HEIGHT = 50;
const int HEIGHTS[5] = {
  75,   // Bottom limit
  250,  // Intake for blocks placed on top of another block - NEED TO ADJUST
  485,  // Place block in low tower
  525,  // Remove block from low tower
  700   // Place block in mid tower
};
