#ifndef VISION_H
#define VISION_H

#include <stdbool.h>
#include <stdint.h>

#include "../hal/sensor_constants.h"

/**
 * @struct sensor_state
 * @brief Structure to hold the state of the sensors.
 */
typedef struct {
    uint8_t central_sensors_state;  // The state of the central sensors.
    bool central_sensor;  // Flag to indicate if the central sensor is active.
    bool left_sensor;     // Flag to indicate if the left sensor is active.
    bool right_sensor;    // Flag to indicate if the right sensor is active.
    bool middle_sensor;   // Flag to indicate if the middle sensor is active.
} SensorState;

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
SensorState* get_sensors(void);

#endif  // VISION_H
