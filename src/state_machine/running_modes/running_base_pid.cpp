#include "../../../include/state_machine/running_modes/running_base_pid.h"

#include "../../../include/logger/logger.h"
#include "../../../include/pid/pid.h"
#include "../../../include/receiver/receiver.h"
#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/state_machine/running_modes/running_base.h"
#include "../../../include/timer/time.h"
#include "../../../include/vision/track.h"

#define BREAK_PWM 60
#define CURVE_1_ACCELERATION_TIME 500

static bool started = false;
static bool can_accelerate = false;

static bool started_curve_1 = false;
static uint32_t curve_1_time;

static void accelerate(const PidStruct* pid) {
    if (pid->current_pwm < pid->base_pwm) set_current_pwm(pid->current_pwm + 1);
}

static void update_pwm(const TrackCounters* track) {
    if (!started && track->marker_counter == 1) {
        can_accelerate = true;
        started = true;
    } else if (track->curve_counter == 1) {
        if (!started_curve_1) {
            set_current_pwm(BREAK_PWM);
            curve_1_time = time();
            can_accelerate = true;
            started_curve_1 = true;
        }

        if (!time_elapsed(curve_1_time, CURVE_1_ACCELERATION_TIME)) return;

        set_current_pwm(BREAK_PWM);
        can_accelerate = false;
    } else if (track->crossing_counter == 3 || track->crossing_counter == 7 ||
               track->crossing_counter == 11 || track->crossing_counter == 13 ||
               track->crossing_counter == 15 || track->crossing_counter == 19) {
        set_current_pwm(BREAK_PWM);
        can_accelerate = false;
    } else if (track->crossing_counter == 1 || track->crossing_counter == 4 ||
               track->crossing_counter == 8 || track->crossing_counter == 12 ||
               track->crossing_counter == 14 || track->crossing_counter == 16 ||
               track->crossing_counter == 20) {
        can_accelerate = true;
    }
}

void running_base_pid(StateMachine* sm) {
    debug_print("RUNNING_BASE_PID Mode: Handling running logic");

    const TrackCounters* track = get_counters();
    const PidStruct* pid = get_pid();

    started = false;
    restart_pwm();

    if (sm->log_data) send_start_signal();
    set_start_time();

    while (sm->can_run) {
        if (update_pid()) {
            if (sm->log_data) send_vision_data();
            if (can_accelerate) accelerate(pid);
        }
        if (update_track_counters()) update_pwm(track);

        check_stop(sm);
        process_serial_commands();
    }

    if (sm->log_data) send_stop_signal();
    debug_print("Finalizing RUNNING_BASE_PID mode");
}

void running_base_pid_to_stopped(void) {
    const StateMachine* sm = get_state_machine();
    const PidStruct* pid = get_pid();

    const uint8_t max_pwm_save = pid->max_pwm;
    uint8_t max_pwm = max_pwm_save;

    while (pid->max_pwm) {
        if (!update_pid()) continue;

        set_max_pwm(--max_pwm);

        if (sm->log_data) send_vision_data();
    }

    set_max_pwm(max_pwm_save);
}
