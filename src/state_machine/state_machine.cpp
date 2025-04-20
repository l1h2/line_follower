#include "../../include/state_machine/state_machine.h"

#include "../../include/logger/logger_debug.h"
#include "../../include/pid/pid.h"
#include "../../include/state_machine/state_handler.h"
#include "../../include/state_machine/transition_handler.h"

void state_machine_init(StateMachine* sm, const uint8_t laps) {
    sm->previous_state = STATE_INIT;
    sm->current_state = STATE_INIT;
    sm->next_state = STATE_INIT;
    sm->running_mode = RUNNING_INIT;
    sm->lap = 0;
    sm->laps = laps;
}

void reset_state_machine(StateMachine* sm) {
    sm->previous_state = STATE_INIT;
    sm->current_state = STATE_INIT;
    sm->next_state = STATE_INIT;
    sm->running_mode = RUNNING_INIT;
    sm->lap = 0;
}

void run_state_machine(const uint8_t laps) {
    print("Starting State Machine...");
    StateMachine sm;

    state_machine_init(&sm, laps);

    while (sm.current_state != STATE_STOPPED &&
           sm.current_state != STATE_ERROR) {
        handle_state(&sm);

        if (sm.current_state != sm.next_state) {
            request_transition(&sm);
        }
    }
}
