#include "../../../include/state_machine/base_states/init.h"

#include "../../../include/logger/logger_debug.h"
#include "../../../include/pid/pid.h"

void handle_init(StateMachine* sm) {
    print("INIT State: Initializing PID and other components");
    pid_init();
    sm->next_state = STATE_IDLE;
}

void handle_init_to_idle(void) { print("Transitioning from INIT to IDLE"); }

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
