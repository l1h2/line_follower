#include "../../../include/state_machine/states/stopped.h"

#include "../../../include/logger/logger.h"

void handle_stopped(void) { print("STOPPED State: Handling stopped logic"); }

bool handle_stopped_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        default:
            return false;
    }

    return true;
}
