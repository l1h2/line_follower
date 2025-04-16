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
 * @param errors Pointer to the ErrorStruct to be updated.
 */
void update_sensors(SensorState *sensors);

#endif  // VISION_H
