#include "../../../include/state_machine/running_modes/running_base.h"

#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/timer/time.h"
#include "../../../include/vision/track.h"

static uint32_t last_check_time = 0;

static const TrackCounters* track = get_counters();

static void check_stop_laps(const StateMachine* sm) {
    set_lap(track->laps);

    if (sm->lap >= sm->laps) set_can_run(false);
}

static void check_stop_time(const StateMachine* sm) {
    if (!time_elapsed(sm->start_time, sm->stop_time)) return;

    set_can_run(false);
}

bool check_start(const StateMachine* sm) {
    if (!check_start_marker()) return false;

    set_start_time();
}

void check_stop(const StateMachine* sm, const bool track_updated) {
    switch (sm->stop_mode) {
        case STOP_MODE_NONE:
            return;
        case STOP_MODE_LAPS:
            if (!track_updated) return;
            check_stop_laps(sm);
            break;
        case STOP_MODE_TIME:
            check_stop_time(sm);
            break;
    }
}
