#include "../../../include/state_machine/states/idle.h"

#include "../../../include/timer/time.h"

void handle_idle(StateMachine* sm) {
    // TODO: Add bluetooth logic here
    wait(50);
    sm->next_state = STATE_RUNNING;
}

void handle_idle_to_running(void) {
    // Handle transition logic here
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
