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
	lift_controller.setTarget(HEIGHTS[0]);

	int goal_height = 0;
	int lift_mode = 0;

	Controller controller;
	ControllerButton autonomous_button(ControllerDigital::Y);
	ControllerButton lift_mode_button(ControllerDigital::L2);
	ControllerButton intake_in_button(ControllerDigital::A);
	ControllerButton intake_out_button(ControllerDigital::B);
	ControllerButton intake_out_slow_button(ControllerDigital::X);
	ControllerButton lift_up_button(ControllerDigital::up);
	ControllerButton lift_down_button(ControllerDigital::down);
	ControllerButton push_forward_button(ControllerDigital::R1);
	ControllerButton push_backward_button(ControllerDigital::L1);

	pros::lcd::initialize();

	while (true)
	{
		// Autonomous debug button
		if (autonomous_button.changedToPressed()) autonomous();

		// Intake control
		if (intake_in_button.isPressed()) INTAKE_MOTORS.moveVoltage(12000);
		else if (intake_out_button.isPressed()) INTAKE_MOTORS.moveVoltage(-12000);
		else if (intake_out_slow_button.isPressed()) INTAKE_MOTORS.moveVoltage(-4000);
		else INTAKE_MOTORS.moveVoltage(0);

		// Lift control
		if (lift_mode_button.changedToPressed())
		{
			lift_mode++;
			pros::lcd::print(0, (lift_mode % 2 == 0) ? "Lift mode: PID" : "Lift mode: Manual voltage");
		}

		// Odd lift mode = PID
		if (lift_mode % 2 == 0)
		{
			if (lift_up_button.changedToPressed() && goal_height < NUM_HEIGHTS - 1)
			{
				goal_height++;
				pros::lcd::print(1, "Height setting last at: %d", goal_height);
				lift_controller.setTarget(HEIGHTS[goal_height]);
			}
			else if (lift_down_button.changedToPressed() && goal_height > 0)
			{
				goal_height--;
				pros::lcd::print(1, "Height setting last at: %d", goal_height);
				lift_controller.setTarget(HEIGHTS[goal_height]);
			}
		}
		// Even lift mode = Manual voltage control
		else if (lift_mode % 2 == 1)
		{
			if (lift_up_button.isPressed()) LIFT_MOTOR.moveVoltage(12000);
			else if (lift_down_button.isPressed()) LIFT_MOTOR.moveVoltage(-12000);
			else LIFT_MOTOR.moveVoltage(0);
		}

		// Stack push control
		if (push_forward_button.isPressed()) PUSH_MOTOR.moveVoltage(12000);
		else if (push_backward_button.isPressed()) PUSH_MOTOR.moveVoltage(-12000);

		// Arcade drive with left and right sticks
		chassis.arcade(controller.getAnalog(ControllerAnalog::leftY) * CONT_Y_MODIFIER,
							     controller.getAnalog(ControllerAnalog::leftX) * CONT_X_MODIFIER);

		pros::delay(10);
	}
}
