/* trinity_2015_smallbot.ino
 *
 * Entry point for robot. This file should *not* contain a significant
 * amount of code--the actual logic should be in separate files.
 */

// Hack for Arduino IDE
#include <Servo.h>

#include "robot.h"
#include "serial.h"
#include "debug.h"
//#include "state_machine.h"

//StateMachine *s;
void setup () {
  // Initialize serial port
  serial_init(115200);

  robot = new Robot();

  //s = new StateMachine();
  robot->omni->linear_speed = 400;
  robot->omni->commit();
}

void loop () {
  //s.tick();
  robot->move->tick();
  delay(20);
}
