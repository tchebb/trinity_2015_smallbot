/* drive.cpp
 *
 * Drive control code.
 */

#include <Arduino.h>
#include "drive.h"
#include "servomap.h"

#include <Servo.h>
#if REFRESH_INTERVAL != 3000
  #error Continuous rotation servos require you to customize the Arduino \
         Servo library. Please change REFRESH_INTERVAL to 3000.
#endif

Calibration::Calibration(int low, int dead_low, int midpoint, int dead_high, int high) {
  this->low = low;
  this->dead_low = dead_low;
  this->midpoint = midpoint;
  this->dead_high = dead_high;
  this->high = high;
}

DriveServo::DriveServo(int pin, const Calibration *c) {
  this->c = c;
  s.attach(pin);

  // Initialize the servo with a signal in the center of its dead zone.
  speed(0);
}

int DriveServo::get_speed() {
  return c_speed;
}

void DriveServo::speed(int speed) {
  c_speed = speed;

  int raw;
  if (speed > 0) {
    //raw = map(speed, 1, SPEED_RANGE, c->dead_high, c->high);
    //raw = round(c->dead_high + ((mapping[speed] / 100) * (c->high - c->dead_high)));
    raw = round(c->dead_high + (servo_map[speed] * 120));
  } else if (speed < 0) {
    //raw = map(speed, -SPEED_RANGE, -1, c->low, c->dead_low);
    //raw = round(c->dead_low - ((mapping[-speed] / 100) * (c->dead_low - c->low)));
    raw = round(c->dead_low - (servo_map[-speed] * 120));
  } else {
    raw = c->midpoint;
  }
  s.writeMicroseconds(raw);
}

