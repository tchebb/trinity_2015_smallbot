/* trinity_2015_smallbot.ino
 *
 * Entry point for robot. This file should *not* contain a significant
 * amount of code--the actual logic should be in separate files.
 */

#include "serial.h"
#include "debug.h"

void setup () {
  // Initialize serial port
  serial_init(9600);
}

void loop () {
  // We're in debugging mode for the moment.
  debug_loop();
}
