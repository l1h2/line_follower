#include "../../../include/state_machine/states/idle.h"

#include "../../../include/logger/logger.h"
#include "../../../include/state_machine/handlers/state_request_handler.h"
#include "../../../include/timer/time.h"

void set_running_mode(StateMachine* sm, RunningModes mode) {
    sm->running_mode = mode;
}

void handle_idle(StateMachine* sm) {
    // TODO: Add bluetooth logic here
    print("IDLE State: Waiting for 5 seconds and selecting running mode");
    wait(500);
    set_running_mode(sm, RUNNING_BASE_PID);
    print("Finished selecting running mode in IDLE State");
    request_next_state(sm, STATE_RUNNING);
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
