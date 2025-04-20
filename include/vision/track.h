#ifndef TRACK_H
#define TRACK_H

#include "../../include/pid/errors.h"

#define DETECTION_DEBOUNCE_TIME 1  // Debounce time for detection in deciseconds

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

/**
 * @brief Updates the tracking counters based on the error struct.
 * @param errors Pointer to the ErrorStruct to be updated.
 */
void update_counters(const ErrorStruct *errors);

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
 * @param errors Pointer to the ErrorStruct to be checked.
 * @return True if the robot should break, false otherwise.
 */
bool check_break(const ErrorStruct *errors);

/**
 * @brief Checks if the robot should stop based on the error struct and number
 * of laps.
 * @param errors Pointer to the ErrorStruct to be checked.
 * @return True if the robot should stop, false otherwise.
 */
bool check_stop(const ErrorStruct *errors);

#endif  // TRACK_H
