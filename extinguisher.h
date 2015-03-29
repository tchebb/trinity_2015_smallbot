/* extinguisher.h
 * Header file for extinguisher functions.
 */

#ifndef EXTINGUISHER_H
#define EXTINGUISHER_H

#include <Servo.h>

class Extinguisher {
  public:
  Extinguisher(int pin);
  void extinguish();

  private:
  int pin;
  Servo s;
};

#endif
