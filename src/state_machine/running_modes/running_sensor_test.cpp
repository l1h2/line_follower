#include "../../../include/state_machine/running_modes/running_sensor_test.h"

#include "../../../include/logger/logger.h"
#include "../../../include/pid/errors.h"
#include "../../../include/vision/track.h"

void running_sensor_test(StateMachine* sm) {
    print("RUNNING_SENSOR_TEST Mode: Handling running logic");

    while (true) {
        print_diagnostics(100);
        update_errors();
    }

    print("Finalizing RUNNING_SENSOR_TEST mode");
}

void running_sensor_test_to_stopped(void) {
    // TODO: Implement the logic to stop the sensor test mode
}
