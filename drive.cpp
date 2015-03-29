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

#define SERVO_RANGE 120

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
    raw = round(c->dead_high + (map_entry_at(speed) * SERVO_RANGE));
  } else if (speed < 0) {
    raw = round(c->dead_low - (map_entry_at(-speed) * SERVO_RANGE));
  } else {
    raw = c->midpoint;
  }
  s.writeMicroseconds(raw);
}

