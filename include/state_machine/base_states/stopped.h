#ifndef STOPPED_STATE_H
#define STOPPED_STATE_H

#include <stdbool.h>

#include "../state_machine_base.h"

/**
 * @brief Handles the stopped state logic.
 */
void handle_stopped(void);

/**
 * @brief Handles the transitions within the stopped state.
 * @param sm Pointer to the state machine structure.
 */
bool handle_stopped_transitions(StateMachine* sm);

#endif  // STOPPED_STATE_H
