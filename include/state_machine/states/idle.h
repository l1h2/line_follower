#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include <stdbool.h>

#include "../state_machine_base.h"

/**
 * @brief Handles the idle state logic.
 * @param sm Pointer to the state machine structure.
 */
void handle_idle(StateMachine* sm);

/**
 * @brief Handles the transitions within the idle state.
 * @param sm Pointer to the state machine structure.
 * @return true if the transition was successful, false otherwise.
 */
bool handle_idle_transitions(StateMachine* sm);

#endif  // IDLE_STATE_H
