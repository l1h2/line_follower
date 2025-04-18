#ifndef TRANSITION_HANDLER_H
#define TRANSITION_HANDLER_H

#include <stdbool.h>

#include "state_machine_base.h"

/**
 * @brief Updates the state machine's current state.
 * @param sm Pointer to the state machine structure.
 */
void update_state(StateMachine* sm);

/**
 * @brief Handles the transition logic for the state machine.
 * @param sm Pointer to the state machine structure.
 * @return true if the transition was successful, false otherwise.
 */
bool handle_transition(StateMachine* sm);

/**
 * @brief Validates the state transition request.
 * @param sm Pointer to the state machine structure.
 * @return true if the request is valid, false otherwise.
 */
bool validate_request(StateMachine* sm);

/**
 * @brief Requests a state transition for the state machine.
 * @param sm Pointer to the state machine structure.
 * @return true if the transition was successful, false otherwise.
 */
bool request_transition(StateMachine* sm);

#endif  // TRANSITION_HANDLER_H
