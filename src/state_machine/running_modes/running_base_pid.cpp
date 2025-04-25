#include "../../../include/state_machine/running_modes/running_base_pid.h"

#include "../../../include/logger/logger.h"
#include "../../../include/pid/pid.h"
#include "../../../include/vision/track.h"

void running_base_pid(StateMachine* sm) {
    print("RUNNING_BASE_PID Mode: Handling running logic");

    // Assigning lap variables to local scope to reduce number of
    // dereferences in the main execution loop
    uint8_t lap = sm->lap;
    const uint8_t laps = sm->laps;

    while (lap < laps) {
        update_pid();
        if (check_stop()) {
            sm->lap++;
            lap++;
        }
    }

    print("Finalizing RUNNING_BASE_PID mode");
}

void running_base_pid_to_stopped(void) {
    const uint8_t break_speed = get_base_pwm() / BREAK_FRAMES;
    uint8_t base_pwm = get_base_pwm();

    while (base_pwm > 0) {
        base_pwm = (base_pwm <= break_speed) ? 0 : (base_pwm - break_speed);
        set_base_pwm(base_pwm);
        update_pid();

        base_pwm = get_base_pwm();  // Confirm base_pwm after set_base_pwm()
    }
}
