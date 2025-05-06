#ifndef VISION_H
#define VISION_H

#include <stdbool.h>
#include <stdint.h>

#include "vision_base.h"

/**
 * @brief Initializes the sensors and sets up the error struct.
 */
void sensors_init(void);

/**
 * @brief Updates the sensor states in the error struct.
 */
void update_sensors(void);

/**
 * @brief Clears the sensor states in the error struct.
 */
void clear_sensors(void);

/**
 * @brief Returns a pointer to the sensor state structure.
 * @return Pointer to the sensor state structure.
 */
const SensorState* get_sensors(void);

#endif  // VISION_H
