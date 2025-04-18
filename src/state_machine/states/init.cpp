#include "../../../include/state_machine/states/init.h"

#include "../../../include/pid/pid.h"

void handle_init(StateMachine* sm) {
    pid_init();
    sm->next_state = STATE_IDLE;
}

void handle_init_to_idle(void) {
    // Handle transition logic here
}

bool handle_init_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        case STATE_IDLE:
            handle_init_to_idle();
            break;
        default:
            return false;
    }

    return true;
}
