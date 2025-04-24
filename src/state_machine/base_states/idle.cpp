#include "../../../include/state_machine/base_states/idle.h"

#include "../../../include/logger/logger_debug.h"
#include "../../../include/timer/time.h"

void handle_idle(StateMachine* sm) {
    // TODO: Add bluetooth logic here
    print("IDLE State: Waiting for 5 seconds and selecting running mode");
    wait(500);
    sm->running_mode = RUNNING_BASE_PID;
    print("Running mode set to RUNNING_BASE_PID");
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
