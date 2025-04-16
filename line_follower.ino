#define DEBUG_MODE

#include "include/logger/logger_debug.h"
#include "include/pid/pid.h"
#include "include/timer/time.h"
#include "include/vision/track.h"

#define LAPS 10  // Number of laps to run

void setup(void) {
    start_timer();  // Initialize the timer for system time tracking
    pid_init();
    logger_init();
}

int main(void) {
    setup();

    ErrorStruct error = {0};
    wait(50);  // Wait for 5 seconds before starting the PID loop

    while (!check_stop(&error, LAPS)) {
        print_diagnostics(&error, 10);
        update_pid(&error);
    }

    stop(&error);

    return 0;
}
