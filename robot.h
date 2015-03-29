/* robot.h
 * Robot-specific information (pin assignments, mostly).
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <Servo.h>
#include "drive.h"
#include "omnidrive.h"
#include "extinguisher.h"
#include "movement.h"
#include "sensor.h"

#define DPIN_SERVO_EXTINGUISH    8

#define DPIN_DRIVE_LEFT          11
#define DPIN_DRIVE_RIGHT         10
#define DPIN_DRIVE_REAR          9


#define APIN_LINE                A8
#define APIN_DIST_FRONT          A5
#define APIN_DIST_RIGHT          A6
#define APIN_DIST_LEFT           A4
#define APIN_DIST_BACK           A7
#define APIN_FIRE_FRONT          A1
#define APIN_FIRE_RIGHT          A2
#define APIN_FIRE_LEFT           A0
#define APIN_FIRE_BACK           A3

#define DPIN_FIRE_LED            47
#define DPIN_BUTTON_START        46
#define DPIN_SOUND_DETECT        48

class Robot {
  public:
  Robot();

  Extinguisher *extinguisher;

  Movement *move;

  Sensor *distance_left, *distance_right, *distance_front, *distance_back,
         *flame_left,    *flame_right,    *flame_front,    *flame_back,
         *line;

  //private:
  OmniDrive *omni;
  DriveServo *left_wheel, *right_wheel, *rear_wheel;
};

extern Robot *robot;

#endif
