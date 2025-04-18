#include "../../../include/state_machine/states/running.h"

#include "../../../include/logger/logger_debug.h"
#include "../../../include/vision/track.h"

static ErrorStruct errors = {0};

void handle_running(StateMachine* sm) {
    const uint8_t laps = sm->laps;

    while (!check_stop(&errors, laps)) {
        print_diagnostics(&errors, 10);
        update_pid(&errors);
    }

    sm->next_state = STATE_STOPPED;
}

void handle_running_to_stopped(void) {
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

bool handle_running_transitions(StateMachine* sm) {
    switch (sm->next_state) {
        case STATE_STOPPED:
            handle_running_to_stopped();
            break;
        default:
            return false;
    }

    return true;
}
