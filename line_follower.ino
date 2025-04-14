#include <avr/io.h>
#include <util/delay.h>

#include "include/logger/logger.h"
#include "include/pid/pid.h"

#define DEBUG_MODE true

void setup(void) {
    if (DEBUG_MODE) logger_init();
    pid_init();
}

int main(void) {
    setup();

    error_struct error = {0, 0, 0, 0};

    while (true) {
        if (DEBUG_MODE) {
            print_diagnostics(&error);
            _delay_ms(1000);
        }

        update_pid(&error);
    }

    return 0;
}
