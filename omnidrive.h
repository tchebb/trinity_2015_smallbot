/* omnidrive.h
 * Header files for omni drive.
 */

#ifndef OMNIDRIVE_H
#define OMNIDRIVE_H

#include "drive.h"

class OmniDrive {
  public:
  OmniDrive(DriveServo *left, DriveServo *right, DriveServo *rear);

  int direction;
  int linear_speed;
  int angular_speed;

  void commit();

  private:
  DriveServo *left, *right, *rear;
};

#endif
