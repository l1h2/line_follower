#include "../../../include/state_machine/handlers/state_handler.h"

#include "../../../include/logger/logger.h"
#include "../../../include/state_machine/states/error.h"
#include "../../../include/state_machine/states/idle.h"
#include "../../../include/state_machine/states/init.h"
#include "../../../include/state_machine/states/running.h"
#include "../../../include/state_machine/states/stopped.h"

void handle_state(StateMachine* sm) {
    send_robot_data(sm, 0);

    switch (sm->current_state) {
        case STATE_INIT:
            handle_init(sm);
            break;
        case STATE_IDLE:
            handle_idle(sm);
            break;
        case STATE_RUNNING:
            handle_running(sm);
            break;
        case STATE_STOPPED:
            handle_stopped(sm);
            break;
        case STATE_ERROR:
            handle_error();
            break;
        default:
            debug_print("Unknown state!");
            return;
    }
}
