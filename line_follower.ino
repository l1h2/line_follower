#include <avr/io.h>

#include "include/hal/timer.h"
#include "include/logger/logger.h"
#include "include/pid/pid.h"

#define DEBUG_MODE true

void setup(void) {
    timer_init();  // Initialize the timer for system time tracking
    if (DEBUG_MODE) logger_init();
    pid_init();
}

int main(void) {
    setup();

    error_struct error = {0, 0, 0, 0};

    while (true) {
        if (DEBUG_MODE) print_diagnostics(&error, 10);
        update_pid(&error);
    }

    return 0;
}
