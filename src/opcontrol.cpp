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
	lift_controller.setMaxVelocity(100);
	lift_controller.setTarget(START_HEIGHT);

	int goal_height = 0;

	Controller controller;
	ControllerButton autonomous_button(ControllerDigital::Y);
	ControllerButton intake_in_button(ControllerDigital::A);
	ControllerButton intake_out_slow_button(ControllerDigital::B);
	ControllerButton intake_out_button(ControllerDigital::X);
	ControllerButton lift_up_button(ControllerDigital::R1);
	ControllerButton lift_down_button(ControllerDigital::L1);

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
			lift_controller.setTarget(HEIGHTS[goal_height]);

			// Brain screen update message
			pros::lcd::print(1, "Height: %d", goal_height);
		}
		else if (lift_down_button.changedToPressed() && goal_height > 0)
		{
			goal_height--;
			lift_controller.setTarget(HEIGHTS[goal_height]);

			// Brain screen update message
			pros::lcd::print(1, "Height: %d", goal_height);
		}

		// Arcade drive with left and right sticks
		chassis.arcade(controller.getAnalog(ControllerAnalog::leftY) * CONT_Y_MODIFIER,
							     controller.getAnalog(ControllerAnalog::leftX) * CONT_X_MODIFIER);

		pros::delay(10);
	}
}
