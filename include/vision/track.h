#ifndef TRACK_H
#define TRACK_H

#include <stdbool.h>

#include "vision_base.h"

/**
 * @brief Resets the tracking counters to zero.
 */
void reset_counters(void);

/**
 * @brief Gets the current tracking counters.
 * @return The current tracking counters.
 */
const TrackCounters* get_counters(void);

/**
 * @brief Checks for a start marker based on the error struct.
 * @return True if the robot should start, false otherwise.
 */
bool check_start_marker(void);

/**
 * @brief Update crossings, curves and markers with line characteristics.
 * @return True if counter was updated, false otherwise.
 */
bool update_track_counters(void);

#endif  // TRACK_H
