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

const int DRIVE_MOTOR_LEFT_F = 2;    // Front left drive motor
const int DRIVE_MOTOR_LEFT_B = 11;   // Back left drive motor
const int DRIVE_MOTOR_RIGHT_F = 3;   // Front right drive motor
const int DRIVE_MOTOR_RIGHT_B = 12;  // Back right drive motor

auto chassis = ChassisControllerFactory::create(
	{-DRIVE_MOTOR_LEFT_F, -DRIVE_MOTOR_LEFT_B},  // Left motors
	{DRIVE_MOTOR_RIGHT_F, DRIVE_MOTOR_RIGHT_B}   // Right motors
);

void opcontrol()
{
	Controller controller;

	while (true)
	{
		// Tank drive with left and right sticks
		chassis.tank(controller.getAnalog(ControllerAnalog::leftY),
							 controller.getAnalog(ControllerAnalog::rightY));
	}
}
