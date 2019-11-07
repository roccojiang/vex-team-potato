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
  // Move forward to row of blocks
  profile_controller.generatePath({Point{CHASSIS_LENGTH, 0_in, 0_deg}, Point{33_in, 0_in, 0_deg}}, "A");
  profile_controller.setTarget("A");
  profile_controller.waitUntilSettled();

  // Activate intake
  intake_controller.setTarget(100);  // Maximum velocity 100 for red gearset

  // Continue moving forward through row of blocks, then deactivate intake
  profile_controller.generatePath({Point{33_in, 0_in, 0_deg}, Point{50_in, 0_in, 0_deg}}, "B");
  profile_controller.setTarget("B");
  profile_controller.waitUntilSettled();
  intake_controller.setTarget(0);  // Set velocity to 0
}
