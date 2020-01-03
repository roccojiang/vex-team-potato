#include "main.h"
using namespace okapi;

/**
 * Controller initialisation
 */

// Controllers
Controller controller;
ControllerButton autonomous_button(ControllerDigital::Y);
ControllerButton intake_in_button(ControllerDigital::A);
ControllerButton intake_out_slow_button(ControllerDigital::B);
ControllerButton intake_out_button(ControllerDigital::X);
ControllerButton lift_up_button(ControllerDigital::R1);
ControllerButton lift_down_button(ControllerDigital::L1);


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

const int PUSH_MOTOR_P = 5;

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
const int GEAR_RATIO = 18.0 / 12.0;  // Multiply with green gearset

// Chassis
auto chassis = ChassisControllerBuilder()
  .withMotors(DRIVE_MOTOR_LEFT, -DRIVE_MOTOR_RIGHT)
  .withDimensions(AbstractMotor::gearset::green, {{WHEEL_DIAMETER, CHASSIS_WIDTH}, imev5GreenTPR * GEAR_RATIO})
  .withOdometry()
  .buildOdometry();

// Async controller for intake
auto intake_controller = AsyncVelControllerBuilder()
  .withMotor(INTAKE_MOTORS)
  .build();

// Async controller for lift
auto lift_controller = AsyncPosControllerBuilder()
  .withMotor(LIFT_MOTORS)
  .withMaxVelocity(50)  // red gearset – out of 100 rpm?
  .build();

const int NUM_HEIGHTS = 5;
const int START_HEIGHT = 50;
const int HEIGHTS[5] = {
  75,   // Bottom limit
  250,  // Intake for blocks placed on top of another block - NEED TO ADJUST
  485,  // Place block in low tower
  525,  // Remove block from low tower
  700   // Place block in mid tower
};


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Team Potato");

	pros::lcd::register_btn1_cb(on_center_button);

	pros::delay(100);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol()
{
	lift_controller->setTarget(START_HEIGHT);

	int goal_height = 0;

	pros::lcd::initialize();

	while (true)
	{
		// Autonomous debug button
		if (autonomous_button.changedToPressed()) autonomous();

		// Intake control
		if (intake_in_button.isPressed()) INTAKE_MOTORS.moveVoltage(8000);
		else if (intake_out_button.isPressed()) INTAKE_MOTORS.moveVoltage(-8000);
		else if (intake_out_slow_button.isPressed()) INTAKE_MOTORS.moveVoltage(-4000);
		else INTAKE_MOTORS.moveVoltage(0);

		// Integrated PID lift height control
		if (lift_up_button.changedToPressed() && goal_height < NUM_HEIGHTS - 1)
		{
			goal_height++;
			lift_controller->setTarget(HEIGHTS[goal_height]);

			// Brain screen update message
			pros::lcd::print(1, "Height: %d", goal_height);
		}
		else if (lift_down_button.changedToPressed() && goal_height > 0)
		{
			goal_height--;
			lift_controller->setTarget(HEIGHTS[goal_height]);

			// Brain screen update message
			pros::lcd::print(1, "Height: %d", goal_height);
		}

		// Arcade drive
		chassis->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY) * CONT_Y_MODIFIER,
							     						  controller.getAnalog(ControllerAnalog::leftX) * CONT_X_MODIFIER);

		pros::delay(10);
	}
}
