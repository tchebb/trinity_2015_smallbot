/* drive.h
 *
 * Header file for drive control.
 */

#ifndef DRIVE_H
#define DRIVE_H

#include <Servo.h>

#define SPEED_RANGE 500

class Calibration {
  public:
  Calibration(int low, int dead_low, int midpoint, int dead_high, int high);

  int low, dead_low, midpoint, dead_high, high;
};

class DriveServo {
  public:
  DriveServo(int pin, const Calibration *c);

  void speed(int speed);
  int get_speed();

  private:
  Servo s;
  const Calibration *c;
  int c_speed;
};

#endif
