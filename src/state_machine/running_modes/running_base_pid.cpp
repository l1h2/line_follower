#include "../../../include/state_machine/running_modes/running_base_pid.h"

#include "../../../include/logger/logger_debug.h"
#include "../../../include/pid/pid.h"
#include "../../../include/vision/track.h"

static ErrorStruct errors = {0};

void running_base_pid(StateMachine* sm) {
    print("RUNNING_BASE_PID Mode: Handling running logic");

    // Assigning lap variables to local scope to reduce number of
    // dereferences in the main execution loop
    uint8_t lap = sm->lap;
    const uint8_t laps = sm->laps;

    while (lap < laps) {
        print_diagnostics(&errors, 100);
        update_pid(&errors);
        if (check_stop(&errors)) {
            sm->lap++;
            lap++;
            print_string("Completed lap: ");
            print_byte(lap);
            print_string(" of ");
            print_byte(laps);
            print(" laps");
        }
    }

    print("Finalizing RUNNING_BASE_PID mode");
}

void running_base_pid_to_stopped(void) {
    const uint8_t break_speed = get_base_pwm() / BREAK_FRAMES;
    uint8_t base_pwm = get_base_pwm();

    while (base_pwm > 0) {
        print_diagnostics(&errors, 10);
        base_pwm = (base_pwm <= break_speed) ? 0 : (base_pwm - break_speed);
        set_base_pwm(base_pwm);
        update_pid(&errors);

        base_pwm = get_base_pwm();  // Confirm base_pwm after set_base_pwm()
    }
}
