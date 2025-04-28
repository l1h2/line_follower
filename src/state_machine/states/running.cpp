#include "../../../include/state_machine/states/running.h"

#include "../../../include/logger/logger.h"
#include "../../../include/state_machine/handlers/state_request_handler.h"
#include "../../../include/vision/track.h"

// Running modes
#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/state_machine/running_modes/running_base_pid.h"
#include "../../../include/state_machine/running_modes/running_sensor_test.h"

void handle_running(StateMachine* sm) {
    debug_print("RUNNING State: Choosing running mode");

    switch (sm->running_mode) {
        case RUNNING_INIT:
            debug_print("No running mode set, going back to IDLE state");
            request_next_state(sm, STATE_IDLE);
            return;
        case RUNNING_BASE_PID:
            debug_print("Running mode set to RUNNING_BASE_PID");
            running_base_pid(sm);
            break;
        case RUNNING_SENSOR_TEST:
            debug_print("Running mode set to RUNNING_SENSOR_TEST");
            running_sensor_test(sm);
            break;
        default:
            debug_print("Unknown running mode, program will stop");
            request_next_state(sm, STATE_ERROR);
            return;
    }

    debug_print("Finalizing RUNNING state, preparing to stop");
    request_next_state(sm, STATE_STOPPED);
}

static bool handle_running_to_stopped(const RunningModes running_mode) {
    debug_print("Transitioning from RUNNING to STOPPED");

    switch (running_mode) {
        case RUNNING_BASE_PID:
            running_base_pid_to_stopped();
            break;
        case RUNNING_SENSOR_TEST:
            running_sensor_test_to_stopped();
            break;
        default:
            debug_print("Unknown running mode, going to error state");
            return false;
    }

    debug_print("Base PWM set to 0, stopping motors");
    return true;
}

bool handle_running_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        case STATE_STOPPED:
            return handle_running_to_stopped(sm->running_mode);
        case STATE_IDLE:
            set_can_run(false);
            debug_print("Transitioning from RUNNING to IDLE");
            return true;
        default:
            return false;
    }
}
