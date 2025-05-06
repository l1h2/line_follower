#include "../../../include/state_machine/running_modes/running_base_pid.h"

#include "../../../include/logger/logger.h"
#include "../../../include/pid/pid.h"
#include "../../../include/receiver/receiver.h"
#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/state_machine/running_modes/running_base.h"
#include "../../../include/vision/track.h"

void running_base_pid(const StateMachine* sm) {
    debug_print("RUNNING_BASE_PID Mode: Handling running logic");

    restart_pwm();

    if (sm->log_data) send_start_signal();
    set_start_time();

    while (sm->can_run) {
        if (update_pid()) {
            check_stop(sm, update_track_counters());
            if (sm->log_data) send_vision_data();
        }

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
