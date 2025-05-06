#include "../../../include/state_machine/handlers/state_handler.h"

#include "../../../include/logger/logger.h"
#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/state_machine/states/error.h"
#include "../../../include/state_machine/states/idle.h"
#include "../../../include/state_machine/states/init.h"
#include "../../../include/state_machine/states/running.h"
#include "../../../include/state_machine/states/stopped.h"

static const StateMachine* sm = get_state_machine();

void handle_state(void) {
    send_robot_data(sm, 0);

    switch (sm->current_state) {
        case STATE_INIT:
            handle_init();
            break;
        case STATE_IDLE:
            handle_idle(sm);
            break;
        case STATE_RUNNING:
            handle_running(sm);
            break;
        case STATE_STOPPED:
            handle_stopped();
            break;
        case STATE_ERROR:
            handle_error();
            break;
        default:
            debug_print("Unknown state!");
            return;
    }
}
