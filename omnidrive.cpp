/* omnidrive.cpp
 * Coordinates motion of the three drive wheels to perform high-level motion.
 */

#include "omnidrive.h"
#include <math.h>
#include "robot.h"

static double deg2rad(double deg);

OmniDrive::OmniDrive(DriveServo *left, DriveServo *right, DriveServo *rear) {
  this->left = left;
  this->right = right;
  this->rear = rear;

  direction = 0;
  linear_speed = 0;
  angular_speed = 0;

  commit();
}

void OmniDrive::commit() {
  const double coeff = sqrt(3.0)/2.0;
  
  double direction_rad = deg2rad(direction);
  double x = sin(direction_rad);
  double y = cos(direction_rad);

  double raw_left = (-0.5 * x) - (coeff * y) - angular_speed;
  double raw_right = (-0.5 * x) + (coeff * y) - angular_speed;
  double raw_rear = x - angular_speed;

  left->speed(raw_left * linear_speed);
  right->speed(raw_right * linear_speed);
  rear->speed(raw_rear * linear_speed);
}

static double deg2rad(double deg) {
  return (deg * 2 * M_PI) / 360;
}
