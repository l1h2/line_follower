#include <avr/io.h>

#include "include/hal/timer.h"
#include "include/logger/logger.h"
#include "include/pid/pid.h"

#define DEBUG_MODE

void setup(void) {
    timer_init();  // Initialize the timer for system time tracking
    pid_init();

#ifdef DEBUG_MODE
    logger_init();
#endif
}

int main(void) {
    setup();

    error_struct error = {0, 0, 0, 0, 0};

    while (true) {
#ifdef DEBUG_MODE
        print_diagnostics(&error, 10);
#endif

        update_pid(&error);
    }

    stop(&error);

    return 0;
}
