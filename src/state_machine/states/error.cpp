#include "../../../include/state_machine/states/error.h"

void handle_error(void) {
    // Handle error state logic here
}

void handle_any_to_error(StateMachine* sm) { sm->next_state = STATE_ERROR; }

bool handle_serror_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        default:
            return false;
    }

    return true;
}
