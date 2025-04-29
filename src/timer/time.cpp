#include "../../include/timer/time.h"

#include "../../include/hal/timer.h"

void start_timer(void) { timer_init(); }

void start_debug_timer(void) { debug_timer_init(); }

void stop_debug_timer(void) { debug_timer_stop(); }

uint32_t time(void) { return get_system_time(); }

bool time_elapsed(const uint32_t last_time, const uint32_t interval) {
    return (time() - last_time) >= interval;
}
