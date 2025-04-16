#include "../../include/pid/pid.h"

#include <stdlib.h>

#include "../../include/hal/pwm.h"
#include "../../include/timer/time.h"

static uint16_t last_pid_time = 0;
static uint8_t base_pwm = BASE_PWM;

void pid_init(void) {
    sensors_init();
    motor_setup();
}

int16_t get_p(const ErrorStruct *errors) {
    if (KP == 0) return 0;

    return KP * errors->error;
}

int16_t get_i(const ErrorStruct *errors) {
    if (KI == 0) return 0;

    return KI * errors->error_sum * PID_FRAME_INTERVAL;
}

int16_t get_d(const ErrorStruct *errors) {
    if (KD == 0) return 0;

    return KD * errors->filtered_delta_error / PID_FRAME_INTERVAL;
}

int16_t get_delta_pwm(const ErrorStruct *errors) {
    int16_t delta_pwm = 0;

    delta_pwm += get_p(errors);
    delta_pwm += get_i(errors);
    delta_pwm += get_d(errors);

    return delta_pwm;
}

void update_motors(const int16_t delta_pwm) {
    const int16_t pwm_a = base_pwm - delta_pwm;
    const int16_t pwm_b = base_pwm + delta_pwm;

    set_motor_a_dir(pwm_a > 0);
    set_motor_b_dir(pwm_b > 0);

    set_pwm_a((uint16_t)abs(pwm_a));
    set_pwm_b((uint16_t)abs(pwm_b));
}

void update_pid(ErrorStruct *errors) {
    if (!time_elapsed(last_pid_time, PID_FRAME_INTERVAL)) return;

    last_pid_time = time();
    update_error_struct(errors);  // Maybe move this to bypass time check
    update_motors(get_delta_pwm(errors));
}

void stop(ErrorStruct *errors) {
    const uint8_t break_speed = base_pwm / BREAK_FRAMES;
    while (base_pwm > 0) {
        base_pwm = (base_pwm <= break_speed) ? 0 : (base_pwm - break_speed);
        update_pid(errors);
    }
}
