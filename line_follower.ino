#define DEBUG_MODE

#include "include/logger/logger_debug.h"
#include "include/state_machine/state_machine.h"
#include "include/timer/time.h"

#define LAPS 10  // Number of laps to run

void setup(void) {
    start_timer();  // Initialize the timer for system time tracking
    logger_init();
}

int main(void) {
    setup();
    run_state_machine(LAPS);

    return 0;
}
