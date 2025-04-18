#include "../../include/state_machine/transition_handler.h"

#include "../../include/state_machine/states/error.h"
#include "../../include/state_machine/states/idle.h"
#include "../../include/state_machine/states/init.h"
#include "../../include/state_machine/states/running.h"
#include "../../include/state_machine/states/stopped.h"

void update_state(StateMachine* sm) {
    sm->previous_state = sm->current_state;
    sm->current_state = sm->next_state;
}

bool handle_transition(StateMachine* sm) {
    bool transition_successful = false;

    switch (sm->current_state) {
        case STATE_INIT:
            transition_successful = handle_init_transitions(sm);
            break;
        case STATE_IDLE:
            transition_successful = handle_idle_transitions(sm);
            break;
        case STATE_RUNNING:
            transition_successful = handle_running_transitions(sm);
            break;
        case STATE_STOPPED:
            transition_successful = handle_stopped_transitions(sm);
            break;
        case STATE_ERROR:
            transition_successful = handle_serror_transitions(sm);
            break;
        default:
            transition_successful = false;
            break;
    }

    return transition_successful;
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
