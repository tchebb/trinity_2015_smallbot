/* serial.cpp
 * Functions to handle serial communication
 */

#include <Arduino.h>
#include "serial.h"

char blocking_read ();

/* serial_init
 * Initialize the serial connection.
 *
 * Parameters:
 *   rate: The baud rate to communicate at.
 */
void serial_init (long rate) {
  Serial.begin(rate);
  Serial.println("Waiting for input");
}

/* read_serial_line
 * Read a string from the serial port, blicking if needed.
 *
 * Returns: A statically-allocated buffer containing the string.
 */
char *read_serial_line () {
  static char buffer[256];
  
  int i;
  for (i = 0; i < 256; ++i) {
    buffer[i] = blocking_read();
    if (buffer[i] == '\n' || buffer[i] == '\r') {
      buffer[i] = '\0';
      break;
    }
  }
  
  if (i == 255) {
    buffer[i] = '\0';
    // Flush RX buffer
    while (Serial.read() != -1)
      ;
  }
  return buffer;
}

/* blocking_read
 * Read a character from the serial port, waiting for one if necessary.
 *
 * Returns: The character that was read.
 */
char blocking_read () {
  char result;
  
  result = Serial.read();
  while (result == -1) {
    delay(10);
    result = Serial.read();
  }
  return result;
}
