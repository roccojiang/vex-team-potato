#include "main.h"
using namespace okapi;

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

// Modifier controller sensitivity
const float CONT_X_MODIFIER = 0.3;
const float CONT_Y_MODIFIER = 0.5;

// Motor ports
const int DRIVE_MOTOR_LEFT_F = 2;
const int DRIVE_MOTOR_LEFT_B = 11;
const int DRIVE_MOTOR_RIGHT_F = 3;
const int DRIVE_MOTOR_RIGHT_B = 12;

// Chassis measurements
const auto WHEEL_DIAMETER = 4_in;
const auto CHASSIS_WIDTH = 12.5_in;

auto chassis = ChassisControllerFactory::create(
	{-DRIVE_MOTOR_LEFT_F, -DRIVE_MOTOR_LEFT_B},  // Left motors
	{DRIVE_MOTOR_RIGHT_F, DRIVE_MOTOR_RIGHT_B},   // Right motors
	AbstractMotor::gearset::green,  // Torque gearset
	{WHEEL_DIAMETER, CHASSIS_WIDTH}
);

void opcontrol()
{
	Controller controller;

	while (true)
	{
		// Arcade drive with left and right sticks
		chassis.arcade(controller.getAnalog(ControllerAnalog::rightY) * CONT_Y_MODIFIER,
							     controller.getAnalog(ControllerAnalog::rightX) * CONT_X_MODIFIER);

		pros::delay(10);
	}
}
