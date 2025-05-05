#include "../../../include/state_machine/running_modes/running_base.h"

#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/timer/time.h"
#include "../../../include/vision/track.h"

// Check stop frame interval
#define CHECK_STOP_FRAME_INTERVAL 1 * TIME_MULTIPLIER

static uint32_t last_check_time = 0;

static void check_stop_laps(StateMachine* sm) {
    set_lap(get_counters()->marker_counter >> 1);

    if (sm->lap >= sm->laps) set_can_run(false);
}

static void check_stop_time(StateMachine* sm) {
    if (!time_elapsed(sm->start_time, sm->stop_time)) return;

    set_can_run(false);
}

bool check_start(StateMachine* sm) {
    if (!check_start_marker()) return false;

    set_start_time();
}

void check_stop(StateMachine* sm) {
    if (sm->stop_mode == STOP_MODE_NONE) return;
    if (!time_elapsed(last_check_time, CHECK_STOP_FRAME_INTERVAL)) return;

    switch (sm->stop_mode) {
        case STOP_MODE_LAPS:
            check_stop_laps(sm);
            break;
        case STOP_MODE_TIME:
            check_stop_time(sm);
            break;
    }
}
