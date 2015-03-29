/* movement.cpp
 * Header file for movement algorithms.
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "omnidrive.h"
#include "sensor.h"

enum MovementState {
  STOPPED,
  FOLLOWING_CORRIDOR
};

enum Direction {
  FRONT,
  RIGHT,
  BACK,
  LEFT
};
#define NUM_DIRECTIONS 4

class Movement {
  public:
  Movement(OmniDrive *omni, Sensor *left, Sensor *right, Sensor *front, Sensor *back);

  void tick();
  void turn_left();
  void turn_right();
  Direction direction();

  private:
  OmniDrive *omni;
  Sensor *abs_left, *abs_right, *abs_front, *abs_back;

  Direction driving_direction;
  Sensor *left();
  Sensor *right();

  int trim_compensation(int compensation);
};

#endif
