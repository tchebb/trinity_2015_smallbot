/* extinguisher.cpp
 * Extinguisher servo operation.
 */

#include <Arduino.h>
#include <Servo.h>
#include "extinguisher.h"

#define OFF_POSITION 160
#define ON_POSITION  60

Extinguisher::Extinguisher(int pin) {
  this->pin = pin;
  s.attach(pin);
  s.write(OFF_POSITION);
  delay(750);
  s.detach();
}

void Extinguisher::extinguish() {
  s.attach(pin);
  s.write(ON_POSITION);
  delay(500);
  s.write(OFF_POSITION);
  delay(750);
  s.detach();
}
