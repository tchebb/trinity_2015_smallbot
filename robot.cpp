/* robot.cpp
 * Robot object, with global state and subsystems.
 */

#include "robot.h"

Robot *robot;

Robot::Robot() {
  extinguisher = new Extinguisher(DPIN_SERVO_EXTINGUISH);

  left = new DriveServo(DPIN_DRIVE_LEFT,
      new Calibration(1334, 1418, 1525, 1653));
  right = new DriveServo(DPIN_DRIVE_RIGHT,
      new Calibration(1332, 1462, 1577, 1680));
  rear = new DriveServo(DPIN_DRIVE_REAR,
      new Calibration(1346, 1464, 1571, 1670));

  omni = new OmniDrive(left, right, rear);
}
