/* sensors.cpp
 * Sensor handling.
 */

#include <Arduino.h>
#include "sensor.h"

Sensor::Sensor(int pin) {
  this->pin = pin;
  current_index = 0;
  empty_slots = NUM_READINGS;
}

double Sensor::read() {
  int sum = 0;
  for (int i = empty_slots; i < NUM_READINGS; i++)
    sum += readings[i];
  return (double)sum / (NUM_READINGS - empty_slots);
}

void Sensor::update() {
  readings[current_index++] = analogRead(pin);
  if (current_index >= NUM_READINGS)
    current_index = 0;
}
