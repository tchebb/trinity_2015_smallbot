/* robot.cpp
 * Robot object, with global state and subsystems.
 */

#include <Arduino.h>
#include "robot.h"

Robot *robot;

Robot::Robot() {
  extinguisher = new Extinguisher(DPIN_SERVO_EXTINGUISH);

  left_wheel = new DriveServo(DPIN_DRIVE_LEFT,
      new Calibration(1334, 1416, 1471, 1531, 1653));
  right_wheel = new DriveServo(DPIN_DRIVE_RIGHT,
      new Calibration(1332, 1460, 1519, 1581, 1720));
  rear_wheel = new DriveServo(DPIN_DRIVE_REAR,
      new Calibration(1346, 1460, 1517, 1579, 1670));

  distance_left = new Sensor(APIN_DIST_LEFT);
  distance_right = new Sensor(APIN_DIST_RIGHT);
  distance_front = new Sensor(APIN_DIST_FRONT);
  distance_back = new Sensor(APIN_DIST_BACK);
  flame_left = new Sensor(APIN_DIST_LEFT);
  flame_right = new Sensor(APIN_DIST_RIGHT);
  flame_front = new Sensor(APIN_DIST_FRONT);
  flame_back = new Sensor(APIN_DIST_BACK);
  line = new Sensor(APIN_LINE);

  omni = new OmniDrive(left_wheel, right_wheel, rear_wheel);

  pinMode(DPIN_BUTTON_START, INPUT_PULLUP);
  pinMode(DPIN_FIRE_LED, OUTPUT);
  digitalWrite(DPIN_FIRE_LED, LOW);
  pinMode(DPIN_SOUND_DETECT, INPUT);

  move = new Movement(omni, distance_left, distance_right, distance_front, distance_back);
}
