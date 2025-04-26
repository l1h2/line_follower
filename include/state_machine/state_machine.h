#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdint.h>

#include "state_machine_base.h"

/**
 * @brief Resets the state machine to its initial state.
 * @param sm Pointer to the state machine structure.
 */
void reset_state_machine(StateMachine* sm);

/**
 * @brief Runs the state machine.
 */
void run_state_machine();

#endif  // STATE_MACHINE_H
