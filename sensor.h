/* sensor.h
 * Header for sensor handling.
 */

#ifndef SENSOR_H
#define SENSOR_H

#define NUM_READINGS 5

class Sensor {
  public:
  Sensor(int pin);

  double read();
  void update();

  private:
  int pin;

  int readings[NUM_READINGS];
  int current_index;
  int empty_slots;
};

#endif
