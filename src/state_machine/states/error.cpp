#include "../../../include/state_machine/states/error.h"

#include "../../../include/logger/logger.h"
#include "../../../include/state_machine/handlers/state_request_handler.h"

void handle_error(void) { debug_print("ERROR State: Handling error logic"); }

void handle_any_to_error(StateMachine* sm) {
    debug_print("Transitioning to ERROR State from any state");
    request_next_state(sm, STATE_ERROR);
}

bool handle_error_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        default:
            return false;
    }

    return true;
}
