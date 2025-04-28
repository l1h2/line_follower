#include "../../../include/state_machine/running_modes/running_base.h"

#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/timer/time.h"
#include "../../../include/vision/track.h"

static void check_stop_laps(StateMachine* sm) {
    if (!check_stop_marker()) return;

    add_lap();
    if (sm->lap >= sm->laps) set_can_run(false);
}

static void check_stop_time(StateMachine* sm) {
    if ((time() - sm->start_time) < sm->stop_time) return;

    set_can_run(false);
}

bool check_start(StateMachine* sm) {
    if (!check_start_marker()) return false;

    set_start_time();
}

void check_stop(StateMachine* sm) {
    switch (sm->stop_mode) {
        case STOP_MODE_NONE:
            return;
        case STOP_MODE_LAPS:
            check_stop_laps(sm);
            break;
        case STOP_MODE_TIME:
            check_stop_time(sm);
            break;
    }
}
