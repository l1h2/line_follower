#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include <stdint.h>

#include "state_machine_base.h"

/**
 * @brief Handles the state machine logic based on the current state.
 * @param sm Pointer to the state machine structure.
 */
void handle_state(StateMachine* sm);

#endif  // STATE_HANDLER_H
