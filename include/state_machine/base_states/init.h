#ifndef INIT_STATE_H
#define INIT_STATE_H

#include <stdbool.h>

#include "../state_machine_base.h"

/**
 * @brief Handles the initialization state logic.
 * @param sm Pointer to the state machine structure.
 */
void handle_init(StateMachine* sm);

/**
 * @brief Handles the transition from initialization to idle state.
 */
void handle_init_to_idle(void);

/**
 * @brief Handles the transitions within the initialization state.
 * @param sm Pointer to the state machine structure.
 * @return true if the transition was successful, false otherwise.
 */
bool handle_init_transitions(StateMachine* sm);

#endif  // INIT_STATE_H
