#ifndef RUNNING_STATE_H
#define RUNNING_STATE_H

#include <stdbool.h>
#include <stdint.h>

#include "../state_machine_base.h"

/**
 * @brief Handles the running state logic.
 * @param sm Pointer to the state machine structure.
 */
void handle_running(StateMachine* sm);

/**
 * @brief Handles the transition from running to stopped state.
 * @param running_mode The current running mode of the robot.
 * @return true if the transition was successful, false otherwise.
 */
bool handle_running_to_stopped(const RunningModes running_mode);

/**
 * @brief Handles the transitions within the running state.
 * @param sm Pointer to the state machine structure.
 * @return true if the transition was successful, false otherwise.
 */
bool handle_running_transitions(StateMachine* sm);

#endif  // RUNNING_STATE_H
