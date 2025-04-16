#ifndef VISION_H
#define VISION_H

#include "errors.h"

// Time in us to debounce detection (Highly inaccurate due to machine cycle
// counts)
#define DETECTION_DEBOUNCE_TIME 20000

/**
 * @struct TrackingCounters
 * @brief Structure to hold tracking counters for different line observations.
 */
typedef struct {
    uint16_t line_counter = 0;      // Lines detected
    uint16_t straight_counter = 0;  // Straight lines detected
    uint8_t crossing_counter = 0;   // Crossings detected
    uint8_t curve_counter = 0;      // Curve markers detected
    uint8_t marker_counter = 0;     // Stop/start markers detected
    uint8_t lost_counter = 0;       // Number of times the line is lost
    uint8_t pitch_counter = 0;  // Number of times the line is lost due to pitch
} TrackingCounters;

/**
 * @brief Checks if the line is detected based on the error struct.
 * @param errors Pointer to the ErrorStruct to be checked.
 * @return True if the line is detected, false otherwise.
 */
bool check_line(const ErrorStruct *errors);

/**
 * @brief Checks if the robot is on a straight line based on the error struct.
 * @param errors Pointer to the ErrorStruct to be checked.
 * @return True if the robot is moving straight, false otherwise.
 */
bool check_straight(const ErrorStruct *errors);

/**
 * @brief Checks if the robot is on a crossing on the error struct.
 * @param errors Pointer to the ErrorStruct to be checked.
 * @return True if the robot is crossing a line, false otherwise.
 */
bool check_crossing(const ErrorStruct *errors);

/**
 * @brief Checks if a curve marker is detected based on the error struct.
 * @param errors Pointer to the ErrorStruct to be checked.
 * @return True if the robot is on a curve, false otherwise.
 */
bool check_curve(const ErrorStruct *errors);

/**
 * @brief Checks if a stop/start marker is detected based on the error struct.
 * @param errors Pointer to the ErrorStruct to be checked.
 * @return True if the robot is on a marker, false otherwise.
 */
bool check_marker(const ErrorStruct *errors);

/**
 * @brief Checks if the line is lost based on the error struct.
 * @param errors Pointer to the ErrorStruct to be checked.
 * @return True if the line is lost, false otherwise.
 */
bool check_lost(const ErrorStruct *errors);

/**
 * @brief Checks if the robot is pitched based on the error struct.
 * @param errors Pointer to the ErrorStruct to be checked.
 * @return True if the robot is pitched, false otherwise.
 */
bool check_pitch(const ErrorStruct *errors);

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
TrackingCounters get_counters(void);

/**
 * @brief Checks if the robot should stop based on the error struct and number
 * of laps.
 * @param errors Pointer to the ErrorStruct to be checked.
 * @param laps The number of laps to complete.
 * @return True if the robot should stop, false otherwise.
 * @note This function uses a highly inaccurate debounce timer to prevent
 * blocking operations.
 */
bool check_stop(const ErrorStruct *errors, const uint8_t laps);

#endif  // VISION_H
