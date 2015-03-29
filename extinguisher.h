/* extinguisher.h
 * Header file for extinguisher functions.
 */

#ifndef EXTINGUISHER_H
#define EXTINGUISHER_H

#include <Servo.h>

class Extinguisher {
  public:
  Extinguisher(int pin);

  void begin_continuous();
  void end_continuous();
  void extinguish_momentary();

  private:
  int pin;
  Servo s;
};

#endif
