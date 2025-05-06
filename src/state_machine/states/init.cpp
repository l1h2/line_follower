#include "../../../include/state_machine/states/init.h"

#include "../../../include/logger/logger.h"
#include "../../../include/pid/pid.h"
#include "../../../include/state_machine/handlers/state_request_handler.h"

void handle_init(void) {
    debug_print("INIT State: Initializing PID and other components");
    pid_init();
    request_next_state(STATE_IDLE);
}

static void handle_init_to_idle(void) {
    debug_print("Transitioning from INIT to IDLE");
}

bool handle_init_transitions(const RobotStates next_state) {
    switch (next_state) {
        case STATE_IDLE:
            handle_init_to_idle();
            break;
        default:
            return false;
    }

    return true;
}
