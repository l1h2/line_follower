#ifndef OBSERVER_H
#define OBSERVER_H

#include <stdbool.h>

/**
 * @brief Checks if the line is detected based on the error struct.
 * @return True if the line is detected, false otherwise.
 */
bool check_line(void);

/**
 * @brief Checks if the robot is on a straight line based on the error struct.
 * @return True if the robot is moving straight, false otherwise.
 */
bool check_straight(void);

/**
 * @brief Checks if the robot is on a crossing on the error struct.
 * @return True if the robot is crossing a line, false otherwise.
 */
bool check_crossing(void);

/**
 * @brief Checks if a curve marker is detected based on the error struct.
 * @return True if the robot is on a curve, false otherwise.
 */
bool check_curve(void);

/**
 * @brief Checks if a stop/start marker is detected based on the error struct.
 * @return True if the robot is on a marker, false otherwise.
 */
bool check_marker(void);

/**
 * @brief Checks if the line is lost based on the error struct.
 * @return True if the line is lost, false otherwise.
 */
bool check_lost(void);

/**
 * @brief Checks if the line is lost to the left based on the error struct.
 * @return True if the line is lost, false otherwise.
 */
bool check_lost_left(void);

/**
 * @brief Checks if the line is lost to the right based on the error struct.
 * @return True if the line is lost, false otherwise.
 */
bool check_lost_right(void);

/**
 * @brief Checks if the robot is pitched based on the error struct.
 * @return True if the robot is pitched, false otherwise.
 */
bool check_pitch(void);

#endif  // OBSERVER_H