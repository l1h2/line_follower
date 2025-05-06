#include "../../../include/state_machine/states/stopped.h"

#include "../../../include/logger/logger.h"
#include "../../../include/pid/pid.h"
#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/state_machine/handlers/state_request_handler.h"
#include "../../../include/vision/track.h"

void handle_stopped(void) {
    debug_print("STOPPED State: Handling stopped logic");
    request_next_state(STATE_IDLE);
}

static void handle_stopped_to_idle(void) {
    debug_print("Transitioning from STOPPED to IDLE");

    restart_state_machine();
    restart_pwm();
    reset_counters();

    debug_print("State machine restarted, going to IDLE state");
}

bool handle_stopped_transitions(const RobotStates next_state) {
    switch (next_state) {
        case STATE_IDLE:
            handle_stopped_to_idle();
            break;
        default:
            return false;
    }

    return true;
}
