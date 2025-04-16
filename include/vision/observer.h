#ifndef OBSERVER_H
#define OBSERVER_H

#include <stdbool.h>

#include "../../include/pid/errors.h"

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

#endif  // OBSERVER_H