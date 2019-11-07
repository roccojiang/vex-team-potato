#include "main.h"
#include "common.h"
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

void opcontrol()
{
	Controller controller;
	ControllerButton autonomous_button(ControllerDigital::X);
	ControllerButton intake_in_button(ControllerDigital::A);
	ControllerButton intake_out_button(ControllerDigital::B);
	ControllerButton lift_up_button(ControllerDigital::up);
	ControllerButton lift_down_button(ControllerDigital::down);

	while (true)
	{
		if (autonomous_button.changedToPressed()) autonomous();

		if (intake_in_button.isPressed()) INTAKE_MOTORS.moveVoltage(12000);
		else if (intake_out_button.isPressed()) INTAKE_MOTORS.moveVoltage(-12000);
		else INTAKE_MOTORS.moveVoltage(0);

		if (lift_up_button.isPressed()) LIFT_MOTOR.moveVoltage(12000);
		else if (lift_down_button.isPressed()) LIFT_MOTOR.moveVoltage(-12000);
		else LIFT_MOTOR.moveVoltage(0);

		// Arcade drive with left and right sticks
		chassis.arcade(controller.getAnalog(ControllerAnalog::rightY) * CONT_Y_MODIFIER,
							     controller.getAnalog(ControllerAnalog::rightX) * CONT_X_MODIFIER);

		pros::delay(10);
	}
}
