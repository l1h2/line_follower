#ifndef VISION_BASE_H
#define VISION_BASE_H

#include <stdbool.h>
#include <stdint.h>

#include "../config.h"

#define DETECTION_DEBOUNCE_TIME 100 * TIME_MULTIPLIER  // Debounce time

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
 * @struct TrackCounters
 * @brief Structure to hold tracking counters for different line observations.
 */
typedef struct {
    uint16_t line_counter;       // Lines detected
    uint16_t straight_counter;   // Straight lines detected
    uint8_t crossing_counter;    // Crossings detected
    uint8_t curve_counter;       // Curve markers detected
    uint8_t marker_counter;      // Stop/start markers detected
    uint8_t lost_left_counter;   // Times the line is lost to the left
    uint8_t lost_right_counter;  // Times the line is lost to the right
    uint8_t pitch_counter;       // Times the line is lost due to pitch
} TrackCounters;

#endif  // VISION_BASE_H
