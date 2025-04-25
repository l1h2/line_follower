#include "../../../include/state_machine/states/running.h"

#include "../../../include/logger/logger.h"
#include "../../../include/state_machine/handlers/state_request_handler.h"
#include "../../../include/vision/track.h"

// Running modes
#include "../../../include/state_machine/running_modes/running_base_pid.h"
#include "../../../include/state_machine/running_modes/running_sensor_test.h"

void handle_running(StateMachine* sm) {
    print("RUNNING State: Choosing running mode");

    switch (sm->running_mode) {
        case RUNNING_INIT:
            print("No running mode set, program will stop");
            return;
        case RUNNING_BASE_PID:
            print("Running mode set to RUNNING_BASE_PID");
            running_base_pid(sm);
            break;
        case RUNNING_SENSOR_TEST:
            print("Running mode set to RUNNING_SENSOR_TEST");
            running_sensor_test(sm);
            break;
        default:
            print("Unknown running mode, program will stop");
            return;
    }

    print("Finalizing RUNNING state, preparing to stop");
    request_next_state(sm, STATE_STOPPED);
}

bool handle_running_to_stopped(const RunningModes running_mode) {
    print("Transitioning from RUNNING to STOPPED");

    switch (running_mode) {
        case RUNNING_BASE_PID:
            running_base_pid_to_stopped();
            break;
        case RUNNING_SENSOR_TEST:
            running_sensor_test_to_stopped();
            break;
        default:
            print("Unknown running mode, going to error state");
            return false;
    }

    print("Base PWM set to 0, stopping motors");
    return true;
}

bool handle_running_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        case STATE_STOPPED:
            return handle_running_to_stopped(sm->running_mode);
        default:
            return false;
    }
}
