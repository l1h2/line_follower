#ifndef RUNNING_BASE_PID_H
#define RUNNING_BASE_PID_H

#include "../state_machine_base.h"

/**
 * @brief Handles the running base PID mode logic.
 * @param sm Pointer to the state machine structure.
 */
void running_base_pid(StateMachine* sm);

/**
 * @brief Handles the transition from running base PID mode to stopped state.
 */
void running_base_pid_to_stopped(void);

#endif  // RUNNING_BASE_PID_H
