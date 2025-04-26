#include "../../include/state_machine/state_machine.h"

#include "../../include/logger/logger.h"
#include "../../include/pid/pid.h"
#include "../../include/state_machine/handlers/state_handler.h"
#include "../../include/state_machine/handlers/transition_handler.h"

static void state_machine_init(StateMachine* sm) {
    sm->previous_state = STATE_INIT;
    sm->current_state = STATE_INIT;
    sm->next_state = STATE_INIT;
    sm->running_mode = RUNNING_INIT;
    sm->stop_mode = STOP_MODE_NONE;
    sm->lap = 0;
    sm->laps = 0;
    sm->stop_time = 0;
}

void reset_state_machine(StateMachine* sm) {
    sm->previous_state = STATE_INIT;
    sm->current_state = STATE_INIT;
    sm->next_state = STATE_INIT;
    sm->running_mode = RUNNING_INIT;
    sm->stop_mode = STOP_MODE_NONE;
    sm->lap = 0;
    sm->laps = 0;
    sm->stop_time = 0;
}

void run_state_machine() {
    debug_print("Starting State Machine...");
    StateMachine sm;

    state_machine_init(&sm);

    while (sm.current_state != STATE_STOPPED &&
           sm.current_state != STATE_ERROR) {
        handle_state(&sm);

        if (sm.current_state != sm.next_state) {
            request_transition(&sm);
        }
    }
}
