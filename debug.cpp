/* debug.cpp
 * Functions for development and debugging of the software.
 */

#include <Arduino.h>
#include "robot.h"
#include "serial.h"
#include "drive.h"
#include "omnidrive.h"
#include "debug.h"

/* debug_loop
 * A main()-like function which provides an interactive prompt to debug the
 * software.
 */
void debug_loop () {
  char *cmd = read_serial_line();
  
  if (strcmp(cmd, "ping") == 0) {
    Serial.println("pong");
  } else if (strcmp(cmd, "raw_flame") == 0) {
    Serial.print("Flame sensor pin values: ");
    Serial.print(analogRead(0)); Serial.print(", ");
    Serial.print(analogRead(1)); Serial.print(", ");
    Serial.print(analogRead(2)); Serial.print(", ");
    Serial.print(analogRead(3)); Serial.print("\n");
    delay(100);
  } else if (strcmp(cmd, "raw_distance") == 0) {
    Serial.print("Distance sensor pin values: ");
    Serial.print(analogRead(4)); Serial.print(", ");
    Serial.print(analogRead(5)); Serial.print(", ");
    Serial.print(analogRead(6)); Serial.print(", ");
    Serial.print(analogRead(7)); Serial.print("\n");
    delay(100);
  }/* else if (strcmp(cmd, "demo_cr") == 0) {
    int i = 0;
    while (i <= SPEED_RANGE) {
      robot->left->speed(i);
      robot->right->speed(i);
      robot->rear->speed(i);
      ++i;
      delay(10);
    }
    delay(100);
    while (i >= -SPEED_RANGE) {
      robot->left->speed(i);
      robot->right->speed(i);
      robot->rear->speed(i);
      --i;
      delay(10);
    }
    delay(100);
    while (i <= 0) {
      robot->left->speed(i);
      robot->right->speed(i);
      robot->rear->speed(i);
      ++i;
      delay(10);
    }
  } else if (strcmp(cmd, "demo_move") == 0) {
    robot->omni->direction = 0;
    robot->omni->linear_speed = 500;
    robot->omni->commit();
    delay(1000);

    robot->omni->linear_speed = 0;
    robot->omni->commit();
    delay(500);

    robot->omni->direction = 90;
    robot->omni->linear_speed = 500;
    robot->omni->commit();
    delay(1000);

    robot->omni->linear_speed = 0;
    robot->omni->commit();
  }*/ else if (strcmp(cmd, "extinguish") == 0) {
    robot->extinguisher->extinguish_momentary();
  }/* else if (strcmp(cmd, "circle") == 0) {
    robot->omni->linear_speed = 400;

    int dir = 270;
    do {
      robot->omni->direction = dir;
      robot->omni->commit();

      dir++;
      if (dir > 360)
        dir = 0;

      delay(30);
    } while (dir != 270);

    robot->omni->linear_speed = 0;
    robot->omni->commit();
  }*/
}
