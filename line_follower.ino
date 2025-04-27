#include "include/config.h"
#include "include/logger/logger.h"
#include "include/receiver/receiver.h"
#include "include/state_machine/state_machine.h"
#include "include/timer/time.h"

void setup(void) {
    start_timer();  // Initialize the timer for system time tracking
    logger_init();
    receiver_init();
}

int main(void) {
    setup();

    // while (true) {
    //     print_string("KP:");
    //     print_char(37);
    //     print_new_line();
    //     print_string("R_MODE:");
    //     print_char(1);
    //     print_new_line();
    //     wait(100);
    // }

    run_state_machine();

    return 0;
}
