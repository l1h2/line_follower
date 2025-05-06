#ifndef RUNNING_BASE_H
#define RUNNING_BASE_H

#include <stdbool.h>

#include "../../state_machine/state_machine_base.h"

/**
 * @brief Checks if the robot should start based on the current state and mode.
 * @param sm Pointer to the state machine structure.
 * @return True if the robot should start, false otherwise.
 */
bool check_start(const StateMachine* sm);

/**
 * @brief Checks if the robot should stop based on the current state and mode.
 * @param sm Pointer to the state machine structure.
 * @param track_updated Indicates if the track has been updated.
 */
void check_stop(const StateMachine* sm, const bool track_updated);

#endif  // RUNNING_BASE_H
