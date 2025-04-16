#ifndef SENSOR_CONSTANTS_H
#define SENSOR_CONSTANTS_H

/**
 * @file sensor_constants.h
 * @brief This file contains hardware-related constants that define the total
 * number of sensors and central sensors in the system.
 *
 * @details These constants are separated from the main sensors.h file to allow
 * selective exposure of hardware specifications to other parts of the codebase
 * (e.g., vision.h) without exposing the entire HAL (Hardware Abstraction
 * Layer). This ensures encapsulation of hardware-specific details while
 * maintaining consistency across the project.
 */

#define TOTAL_SENSORS 12         // Total number of sensors
#define TOTAL_CENTRAL_SENSORS 8  // Total number of central sensors

#endif  // SENSOR_CONSTANTS_H
