#ifndef TRACK_H
#define TRACK_H

#define DETECTION_DEBOUNCE_TIME 1  // Debounce time for detection in deciseconds

#include "../../include/pid/errors.h"

/**
 * @struct TrackCounters
 * @brief Structure to hold tracking counters for different line observations.
 */
typedef struct {
    uint16_t line_counter;      // Lines detected
    uint16_t straight_counter;  // Straight lines detected
    uint8_t crossing_counter;   // Crossings detected
    uint8_t curve_counter;      // Curve markers detected
    uint8_t marker_counter;     // Stop/start markers detected
    uint8_t lost_counter;       // Number of times the line is lost
    uint8_t pitch_counter;      // Number of times the line is lost due to pitch
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
 * @param laps The number of laps to complete.
 * @return True if the robot should stop, false otherwise.
 */
bool check_stop(const ErrorStruct *errors, const uint8_t laps);

#endif  // TRACK_H
