#include "main.h"
#include "common.h"
using namespace okapi;

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
void autonomous()
{
  chassis.moveDistance(30_in);
  /*
  // Move lift up slightly
  lift_controller.setTarget(START_HEIGHT);

  // Push out starting block
  chassis.moveDistanceAsync(30_in);
  INTAKE_MOTORS.moveVoltage(-10000);
  pros::delay(2000);
  INTAKE_MOTORS.moveVoltage(0);

  // Move backwards
  chassis.moveDistance(-50_in);
  */
}
