/* servomap.h
 * Header file for servo mappings.
 */

#ifndef SERVOMAP_H
#define SERVOMAP_H

#include <avr/pgmspace.h>

extern const PROGMEM double servo_map[];

double map_entry_at(int index);

#endif
