#include "../../include/state_machine/transition_handler.h"

#include "../../include/state_machine/base_states/error.h"
#include "../../include/state_machine/base_states/idle.h"
#include "../../include/state_machine/base_states/init.h"
#include "../../include/state_machine/base_states/running.h"
#include "../../include/state_machine/base_states/stopped.h"

void update_state(StateMachine* sm) {
    sm->previous_state = sm->current_state;
    sm->current_state = sm->next_state;
}

bool handle_transition(StateMachine* sm) {
    switch (sm->current_state) {
        case STATE_INIT:
            return handle_init_transitions(sm);
        case STATE_IDLE:
            return handle_idle_transitions(sm);
        case STATE_RUNNING:
            return handle_running_transitions(sm);
        case STATE_STOPPED:
            return handle_stopped_transitions(sm);
        case STATE_ERROR:
            return handle_serror_transitions(sm);
        default:
            return false;
    }
}

bool validate_request(StateMachine* sm) {
    return (sm->next_state != sm->current_state);
}

bool request_transition(StateMachine* sm) {
    if (!validate_request(sm)) return false;

    if (handle_transition(sm)) {
        update_state(sm);
        return true;
    } else {
        handle_any_to_error(sm);
        update_state(sm);
        return false;
    }
}
