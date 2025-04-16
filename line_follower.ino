#define DEBUG_MODE

#include "include/hal/timer.h"
#include "include/logger/logger_debug.h"
#include "include/pid/pid.h"
#include "include/pid/vision.h"

#define LAPS 10  // Number of laps to run

void setup(void) {
    timer_init();  // Initialize the timer for system time tracking
    pid_init();
    logger_init();
}

int main(void) {
    setup();

    ErrorStruct error = {0, 0, 0, 0, 0};
    wait(50);  // Wait for 5 seconds before starting the PID loop

    while (!check_stop(&error, LAPS)) {
        print_diagnostics(&error, 10);
        update_pid(&error);
    }

    stop(&error);

    return 0;
}
