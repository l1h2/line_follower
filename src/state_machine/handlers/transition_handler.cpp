#include "../../../include/state_machine/handlers/transition_handler.h"

#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/state_machine/states/error.h"
#include "../../../include/state_machine/states/idle.h"
#include "../../../include/state_machine/states/init.h"
#include "../../../include/state_machine/states/running.h"
#include "../../../include/state_machine/states/stopped.h"

static StateMachine* sm = get_state_machine_ptr();

void update_state(void) {
    sm->previous_state = sm->current_state;
    sm->current_state = sm->next_state;
}

bool handle_transition(void) {
    switch (sm->current_state) {
        case STATE_INIT:
            return handle_init_transitions(sm->next_state);
        case STATE_IDLE:
            return handle_idle_transitions(sm->next_state);
        case STATE_RUNNING:
            return handle_running_transitions(sm->next_state, sm->running_mode);
        case STATE_STOPPED:
            return handle_stopped_transitions(sm->next_state);
        case STATE_ERROR:
            return handle_error_transitions(sm->next_state);
        default:
            return false;
    }
}

bool validate_transition(void) { return (sm->next_state != sm->current_state); }

bool request_transition(void) {
    if (!validate_transition()) return false;

    if (handle_transition()) {
        update_state();
        return true;
    } else {
        handle_any_to_error();
        update_state();
        return false;
    }
}
