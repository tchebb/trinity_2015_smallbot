/* debug.cpp
 * Functions for development and debugging of the software.
 */

#include <Arduino.h>
#include "serial.h"

/* debug_loop
 * A main()-like function which provides an interactive prompt to debug the
 * software.
 */
void debug_loop () {
  char *cmd = read_serial_line();
  
  if (strcmp(cmd, "ping") == 0) {
    Serial.println("pong");
  }
}
