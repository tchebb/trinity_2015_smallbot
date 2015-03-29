/* movement.cpp
 * Movement algorithms.
 */

#include "movement.h"

#define LOW_DISTANCE  130
#define HIGH_DISTANCE 250

Movement::Movement(OmniDrive *omni, Sensor *left, Sensor *right, Sensor *front, Sensor *back) {
  this->omni = omni;
  abs_left = left;
  abs_right = right;
  abs_front = front;
  abs_back = back;
}

Direction Movement::direction() {
  return driving_direction;
}

Sensor *Movement::left() {
  switch (driving_direction) {
    case FRONT: return abs_left;
    case RIGHT: return abs_front;
    case BACK:  return abs_right;
    case LEFT:  return abs_back;
  }
}

Sensor *Movement::right() {
  switch (driving_direction) {
    case FRONT: return abs_right;
    case RIGHT: return abs_back;
    case BACK:  return abs_left;
    case LEFT:  return abs_front;
  }
}

void Movement::turn_left() {
  driving_direction = (Direction)((int)driving_direction - 1);
  if (driving_direction < 0)
    driving_direction = (Direction)(NUM_DIRECTIONS - 1);
}

void Movement::turn_right() {
  driving_direction = (Direction)((int)driving_direction + 1);
  if (driving_direction >= NUM_DIRECTIONS)
    driving_direction = (Direction)0;
}

void Movement::tick() {
  int left_dist = left()->read();
  int right_dist = right()->read();
  int compensate;

  if (right_dist <= HIGH_DISTANCE && left_dist <= HIGH_DISTANCE) {
    compensate = right_dist - left_dist;
  }
  omni->angular_speed = compensate;
  omni->commit();
}

int Movement::trim_compensation(int compensation) {
  if (compensation > 200) {
    compensation = 200;
  } else if (compensation < -200) {
    compensation = -200;
  }
}
