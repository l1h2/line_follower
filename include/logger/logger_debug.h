#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>

/**
 * @brief Prints the current state of the central sensors in a human-readable
 * format.
 */
void print_central_sensors(void);

/**
 * @brief Prints the current state of the sensors in a human-readable format.
 */
void print_sensors(void);

/**
 * @brief Prints the error values for PID control in a human-readable format.
 */
void print_errors(void);

/**
 * @brief Prints the diagnostics information, including sensor states and error
 * values.
 * @param interval The time interval in centiseconds for printing diagnostics.
 * (Default: 100)
 */
void print_diagnostics(const uint16_t interval = 100);

#endif  // LOGGER_H
