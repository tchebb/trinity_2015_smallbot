/* robot.cpp
 * Robot object, with global state and subsystems.
 */

#include "robot.h"

Robot *robot;

Robot::Robot() {
  extinguisher = new Extinguisher(DPIN_SERVO_EXTINGUISH);

  left = new DriveServo(DPIN_DRIVE_LEFT,
      new Calibration(1334, 1394, 1471, 1555, 1653));
  right = new DriveServo(DPIN_DRIVE_RIGHT,
      new Calibration(1332, 1438, 1519, 1605, 1720));
  rear = new DriveServo(DPIN_DRIVE_REAR,
      new Calibration(1346, 1438, 1517, 1603, 1670));

  omni = new OmniDrive(left, right, rear);
}
