#include "../../include/timer/time.h"

#include "../../include/hal/timer.h"

void start_timer(void) { timer_init(); }

uint16_t time(void) { get_system_time(); }

bool time_elapsed(const uint16_t last_time, const uint16_t interval) {
    const uint16_t current_time = time();
    return (current_time - last_time) >= interval;
}

void wait(const uint16_t interval) {
    const uint16_t start_time = time();
    while (!time_elapsed(start_time, interval));
}
