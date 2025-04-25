#include "../../../include/state_machine/running_modes/running_sensor_test.h"

#include "../../../include/logger/logger.h"
#include "../../../include/pid/errors.h"
#include "../../../include/timer/time.h"
#include "../../../include/vision/track.h"

void running_sensor_test(StateMachine* sm) {
    print("RUNNING_SENSOR_TEST Mode: Handling running logic");

    while (true) {
        print_diagnostics();

        send_start_signal();
        print_vision_data();
        send_stop_signal();

        wait(100);
        update_errors();
    }

    print("Finalizing RUNNING_SENSOR_TEST mode");
}

void running_sensor_test_to_stopped(void) {
    // TODO: Implement the logic to stop the sensor test mode
}
