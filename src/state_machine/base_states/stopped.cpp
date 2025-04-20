#include "../../../include/state_machine/base_states/stopped.h"

#include "../../../include/logger/logger_debug.h"

void handle_stopped(void) { print("STOPPED State: Handling stopped logic"); }

bool handle_stopped_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        default:
            return false;
    }

    return true;
}
