#include "../../../include/state_machine/states/idle.h"

#include <util/delay.h>

#include "../../../include/config.h"
#include "../../../include/logger/logger.h"
#include "../../../include/receiver/receiver.h"
#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/state_machine/handlers/state_request_handler.h"

#ifdef BLUETOOTH_MODE
void handle_idle(StateMachine* sm) {
    debug_print("IDLE State: Waiting for bluetooth commands");

    while (!sm->can_run) {
        send_robot_data(sm, process_serial_commands() ? 0 : 1000);
    }

    debug_print("Start command received in IDLE State");
    request_next_state(sm, STATE_RUNNING);
}
#else
void handle_idle(StateMachine* sm) {
    debug_print("IDLE State: Waiting for 5 seconds and selecting running mode");
    _delay_ms(5000);

    set_running_mode(RUNNING_BASE_PID);
    set_stop_mode(STOP_MODE_LAPS);
    set_can_run(true);
    set_laps(2);
    set_stop_time(0);

    debug_print("Finished selecting running mode in IDLE State");
    request_next_state(sm, STATE_RUNNING);
}
#endif

static void handle_idle_to_running(void) {
    debug_print("Transitioning from IDLE to RUNNING");
}

bool handle_idle_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        case STATE_RUNNING:
            handle_idle_to_running();
            break;
        default:
            return false;
    }

    return true;
}
