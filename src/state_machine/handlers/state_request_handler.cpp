#include "../../../include/state_machine/handlers/state_request_handler.h"

bool validate_next_state(StateMachine* sm) {
    return (sm->next_state == sm->current_state);
}

bool request_next_state(StateMachine* sm, RobotStates next_state) {
    if (!validate_next_state) return false;

    sm->next_state = next_state;
    return true;
}
