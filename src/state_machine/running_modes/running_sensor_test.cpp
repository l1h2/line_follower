#include "../../../include/state_machine/running_modes/running_sensor_test.h"

#include <util/delay.h>

#include "../../../include/logger/logger.h"
#include "../../../include/pid/errors.h"
#include "../../../include/receiver/receiver.h"

void running_sensor_test(const StateMachine* sm) {
    debug_print("RUNNING_SENSOR_TEST Mode: Handling running logic");

    while (sm->can_run) {
        debug_print_diagnostics();

        if (sm->log_data) {
            send_start_signal();
            send_vision_data();
            send_stop_signal();
        }

        _delay_ms(1000);
        update_errors();

        process_serial_commands();
    }

    debug_print("Finalizing RUNNING_SENSOR_TEST mode");
}

void running_sensor_test_to_stopped(void) {
    // TODO: Implement the logic to stop the sensor test mode
}
