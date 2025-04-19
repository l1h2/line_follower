#include "../../include/state_machine/state_handler.h"

#include "../../include/logger/logger_debug.h"
#include "../../include/state_machine/states/error.h"
#include "../../include/state_machine/states/idle.h"
#include "../../include/state_machine/states/init.h"
#include "../../include/state_machine/states/running.h"
#include "../../include/state_machine/states/stopped.h"

void handle_state(StateMachine* sm) {
    switch (sm->current_state) {
        case STATE_INIT:
            print("State: INIT");
            handle_init(sm);
            break;
        case STATE_IDLE:
            print("State: IDLE");
            handle_idle(sm);
            break;
        case STATE_RUNNING:
            print("State: RUNNING");
            handle_running(sm);
            break;
        case STATE_STOPPED:
            print("State: STOPPED");
            handle_stopped();
            break;
        case STATE_ERROR:
            print("State: ERROR");
            handle_error();
            break;
    }
}
