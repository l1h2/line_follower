#ifndef ERROR_STATE_H
#define ERROR_STATE_H

#include <stdbool.h>

#include "../state_machine_base.h"

/**
 * @brief Handles the error state logic.
 */
void handle_error(void);

/**
 * @brief Handles the transition from any state to the error state.
 * @param sm Pointer to the state machine structure.
 */
void handle_any_to_error(StateMachine* sm);

/**
 * @brief Handles the transitions within the error state.
 * @param sm Pointer to the state machine structure.
 * @return true if the transition was successful, false otherwise.
 */
bool handle_error_transitions(StateMachine* sm);

#endif  // ERROR_STATE_H
