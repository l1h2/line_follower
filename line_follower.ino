#include "include/logger/logger.h"
#include "include/receiver/receiver.h"
#include "include/state_machine/state_machine.h"
#include "include/timer/time.h"

void setup(void) {
    start_timer();  // Initialize system time tracking
    logger_init();
    receiver_init();
}

int main(void) {
    setup();

    run_state_machine();

    return 0;
}
