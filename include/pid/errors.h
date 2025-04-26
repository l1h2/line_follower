#ifndef ERRORS_H
#define ERRORS_H

#include <stdint.h>

#include "pid_base.h"

/**
 * @brief Updates the error struct with the latest sensor data and error values.
 */
void update_errors(void);

/**
 * @brief Clears the error struct by resetting its values.
 */
void clear_errors(void);

/**
 * @brief Returns a pointer to the error struct.
 *
 * @return Pointer to the ErrorStruct containing error values.
 */
ErrorStruct* get_errors(void);

#endif  // ERRORS_H
