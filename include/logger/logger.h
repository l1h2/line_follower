#ifndef LOGGER_H
#define LOGGER_H

#include "../../include/logger/logger_base.h"
#include "../pid/pid.h"

/**
 * @brief Prints the current state of the central sensors in a human-readable
 * format.
 * @param sensors The SensorState structure containing the sensor states to be
 * printed.
 */
void print_central_sensors(const SensorState *sensors);

/**
 * @brief Prints the current state of the sensors in a human-readable format.
 * @param sensors The SensorState structure containing the sensor states to be
 * printed.
 */
void print_sensors(const SensorState *sensors);

/**
 * @brief Prints the error values for PID control in a human-readable format.
 * @param errors The ErrorStruct containing the error values.
 */
void print_errors(const ErrorStruct *errors);

/**
 * @brief Prints the diagnostics information, including sensor states and error
 * values.
 * @param errors The ErrorStruct containing the error values.
 * @param interval The time interval in centiseconds for printing diagnostics.
 * (Default: 100)
 */
void print_diagnostics(const ErrorStruct *errors,
                       const uint16_t interval = 100);

#endif  // LOGGER_H
