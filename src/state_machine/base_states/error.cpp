#include "../../../include/state_machine/base_states/error.h"

#include "../../../include/logger/logger_debug.h"

void handle_error(void) { print("ERROR State: Handling error logic"); }

void handle_any_to_error(StateMachine* sm) {
    print("Transitioning to ERROR State from any state");
    sm->next_state = STATE_ERROR;
}

bool handle_serror_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        default:
            return false;
    }

    return true;
}
