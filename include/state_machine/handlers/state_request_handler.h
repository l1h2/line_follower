#ifndef STATE_REQUEST_HANDLER_H
#define STATE_REQUEST_HANDLER_H

#include <stdbool.h>

#include "../state_machine_base.h"

/**
 * @brief Requests the next state for the state machine.
 * @param next_state The next state to transition to.
 * @return true if the next state was successfully set, false otherwise.
 */
bool request_next_state(const RobotStates next_state);

#endif  // STATE_REQUEST_HANDLER_H