#ifndef TRACK_H
#define TRACK_H

#include <stdbool.h>

#include "vision_base.h"

/**
 * @brief Updates the tracking counters based on the error struct.
 */
void update_counters(void);

/**
 * @brief Resets the tracking counters to zero.
 */
void reset_counters(void);

/**
 * @brief Gets the current tracking counters.
 * @return The current tracking counters.
 */
TrackCounters get_counters(void);

/**
 * @brief Checks if the robot is on a crossing based on the error struct.
 * @return True if the robot is on a crossing, false otherwise.
 */
bool check_on_crossing(void);

/**
 * @brief Checks if the robot should break based on the error struct.
 * @return True if the robot should break, false otherwise.
 */
bool check_break(void);

/**
 * @brief Checks for a start marker based on the error struct.
 * @return True if the robot should start, false otherwise.
 */
bool check_start_marker(void);

/**
 * @brief Checks for a stop marker based on the error struct.
 * @return True if the robot should stop, false otherwise.
 */
bool check_stop_marker(void);

#endif  // TRACK_H
