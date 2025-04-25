#ifndef TRANSITION_HANDLER_H
#define TRANSITION_HANDLER_H

#include <stdbool.h>

#include "../state_machine_base.h"

/**
 * @brief Requests a state transition for the state machine.
 * @param sm Pointer to the state machine structure.
 * @return true if the transition was successful, false otherwise.
 */
bool request_transition(StateMachine* sm);

#endif  // TRANSITION_HANDLER_H
