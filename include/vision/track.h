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
 * @brief Checks if the robot should break based on the error struct.
 * @return True if the robot should break, false otherwise.
 */
bool check_break(void);

/**
 * @brief Checks if the robot should stop based on the error struct and number
 * of laps.
 * @return True if the robot should stop, false otherwise.
 */
bool check_stop(void);

#endif  // TRACK_H
