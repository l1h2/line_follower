#include "../../../include/state_machine/running_modes/running_base_pid.h"

#include "../../../include/logger/logger.h"
#include "../../../include/pid/pid.h"
#include "../../../include/receiver/receiver.h"
#include "../../../include/state_machine/handlers/config_handler.h"
#include "../../../include/state_machine/running_modes/running_base.h"

void running_base_pid(StateMachine* sm) {
    debug_print("RUNNING_BASE_PID Mode: Handling running logic");

    if (sm->log_data) send_start_signal();
    set_start_time();

    while (sm->can_run) {
        update_pid();
        if (update_pid() && sm->log_data) send_vision_data();

        check_stop(sm);
        process_serial_commands();
    }

    if (sm->log_data) send_stop_signal();
    debug_print("Finalizing RUNNING_BASE_PID mode");
}

void running_base_pid_to_stopped(void) {
    const StateMachine* sm = get_state_machine();
    const PidStruct* pid = get_pid();
    const uint8_t break_speed =
        pid->max_pwm / (pid->stop_time / pid->frame_interval);

    const uint8_t max_pwm_save = pid->max_pwm;
    uint8_t max_pwm = max_pwm_save;
    bool pid_updated = true;

    while (pid->max_pwm > 0) {
        if (!update_pid()) continue;

        max_pwm = (max_pwm <= break_speed) ? 0 : (max_pwm - break_speed);
        set_max_pwm(max_pwm);

        if (sm->log_data) send_vision_data();
    }

    set_max_pwm(max_pwm_save);
}
