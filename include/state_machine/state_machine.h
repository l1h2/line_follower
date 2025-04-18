#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdint.h>

#include "state_machine_base.h"

/**
 * @brief Initializes the state machine.
 * @param sm Pointer to the state machine structure.
 * @param laps Number of laps to run.
 */
void state_machine_init(StateMachine* sm, const uint8_t laps);

/**
 * @brief Runs the state machine.
 * @param laps Number of laps to run.
 */
void run_state_machine(const uint8_t laps);

#endif  // STATE_MACHINE_H
