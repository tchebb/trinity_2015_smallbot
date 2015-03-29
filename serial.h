/* serial.h
 * Header file for serial functions.
 */

#ifndef SERIAL_H
#define SERIAL_H

#define PRINT_DEBUG 0

#if PRINT_DEBUG
  #define debug(str) Serial.println(str)
#else
  #define debug(str) ((void)0)
#endif

void serial_init (long rate);
char *read_serial_line ();
char blocking_read ();

#endif
