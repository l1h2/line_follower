#include "../../../include/state_machine/states/stopped.h"

void handle_stopped(void) {
    // Handle stopped state logic here
}

bool handle_stopped_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        default:
            return false;
    }

    return true;
}
