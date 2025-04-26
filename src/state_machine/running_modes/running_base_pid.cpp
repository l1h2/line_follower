#include "../../../include/state_machine/running_modes/running_base_pid.h"

#include "../../../include/logger/logger.h"
#include "../../../include/pid/pid.h"
#include "../../../include/vision/track.h"

void running_base_pid(StateMachine* sm) {
    debug_print("RUNNING_BASE_PID Mode: Handling running logic");

    // Assigning lap variables to local scope to reduce number of
    // dereferences in the main execution loop
    uint8_t lap = sm->lap;
    const uint8_t laps = sm->laps;

    send_start_signal();
    while (lap < laps) {
        if (update_pid()) send_vision_data();

        if (check_stop()) {
            sm->lap++;
            lap++;
        }
    }

    send_stop_signal();
    debug_print("Finalizing RUNNING_BASE_PID mode");
}

void running_base_pid_to_stopped(void) {
    const PidStruct* pid = get_pid();
    const uint8_t break_speed =
        pid->max_pwm / (pid->stop_time / pid->frame_interval);

    uint8_t max_pwm = pid->max_pwm;

    while (pid->max_pwm > 0) {
        max_pwm = (max_pwm <= break_speed) ? 0 : (max_pwm - break_speed);
        set_max_pwm(max_pwm);
        update_pid();
    }
}
