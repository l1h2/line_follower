#include "../../../include/state_machine/states/idle.h"

#include "../../../include/logger/logger_debug.h"
#include "../../../include/timer/time.h"

void handle_idle(StateMachine* sm) {
    // TODO: Add bluetooth logic here
    print("IDLE State: Waiting for 50 deciseconds");
    wait(50);
    print("Finished waiting in IDLE State");
    sm->next_state = STATE_RUNNING;
}

void handle_idle_to_running(void) {
    print("Transitioning from IDLE to RUNNING");
}

bool handle_idle_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        case STATE_RUNNING:
            handle_idle_to_running();
            break;
        default:
            return false;
    }

    return true;
}
