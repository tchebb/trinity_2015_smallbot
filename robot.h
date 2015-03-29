/* robot.h
 * Robot-specific information (pin assignments, mostly).
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <Servo.h>
#include "drive.h"
#include "omnidrive.h"
#include "extinguisher.h"

#define DPIN_SERVO_EXTINGUISH    8

#define DPIN_DRIVE_LEFT          11
#define DPIN_DRIVE_RIGHT         10
#define DPIN_DRIVE_REAR          9

class Robot {
  public:
  Robot();

  Extinguisher *extinguisher;

  OmniDrive *omni;

  //private: // For testing
  DriveServo *left, *right, *rear;
};

extern Robot *robot;

#endif
