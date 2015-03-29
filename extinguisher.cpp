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

void Extinguisher::begin_continuous() {
  s.attach(pin);
  s.write(ON_POSITION);
}

void Extinguisher::end_continuous() {
  s.write(OFF_POSITION);
  delay(750);
  s.detach();
}

void Extinguisher::extinguish_momentary() {
  begin_continuous();
  delay(1000);
  end_continuous();
}
