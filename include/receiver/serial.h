#ifndef SERIAL_H
#define SERIAL_H

#include <stdbool.h>

#include "serial_base.h"

/**
 * @brief Processes serial commands received from the serial buffer.
 * @return true if a command was processed, false otherwise.
 */
bool process_serial_commands(void);

#endif  // SERIAL_H
