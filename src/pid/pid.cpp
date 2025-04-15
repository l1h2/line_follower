#include "../../include/pid/pid.h"

#include <stdlib.h>

#include "../../include/hal/pwm.h"
#include "../../include/hal/sensors.h"
#include "../../include/hal/timer.h"

static volatile uint16_t last_pid_time = 0;

void pid_init(void) {
    sensor_setup();
    motor_setup();
}

void update_central_error(error_struct *errors) {
    const uint8_t new_state = CENTRAL_SENSOR_BYTE;
    if (!new_state) {
        if (!IR6_ON) errors->error = 0;
        return;
    }

    errors->central_sensors_state = new_state;
    uint8_t count = 0;
    int8_t new_error = 0;

    for (uint8_t i = 0; i <= 7; i++) {
        if (!(new_state & (1 << i))) continue;

        new_error += i;
        count++;
    }

    errors->error = new_error * ERROR_WEIGHT / count - AVG_ERROR;
}

int16_t get_p(error_struct *errors) {
    if (KP == 0) return 0;

    return KP * errors->error;
}

int16_t get_i(error_struct *errors) {
    if (KI == 0) return 0;

    errors->error_sum += errors->error;

    if (abs(errors->error_sum) < ERROR_SUM_THRESHOLD) return 0;

    if (errors->error_sum > MAX_ERROR_SUM) {
        errors->error_sum = MAX_ERROR_SUM;
    } else if (errors->error_sum < MIN_ERROR_SUM) {
        errors->error_sum = MIN_ERROR_SUM;
    }

    return KI * errors->error_sum * PID_FRAME_INTERVAL;
}

int16_t get_d(error_struct *errors) {
    if (KD == 0) return 0;

    const int16_t delta_error = errors->error - errors->last_error;
    errors->last_error = errors->error;

    errors->filtered_delta_error =
        (errors->filtered_delta_error * 7 + delta_error) >> 3;

    return KD * errors->filtered_delta_error / PID_FRAME_INTERVAL;
}

int16_t get_delta_pwm(error_struct *errors) {
    int16_t delta_pwm = 0;

    delta_pwm += get_p(errors);
    delta_pwm += get_i(errors);
    delta_pwm += get_d(errors);

    return delta_pwm;
}

void update_motors(int16_t delta_pwm) {
    const int16_t pwm_a = BASE_PWM - delta_pwm;
    const int16_t pwm_b = BASE_PWM + delta_pwm;

    set_motor_a_dir(pwm_a > 0);
    set_motor_b_dir(pwm_b > 0);

    set_pwm_a((uint16_t)abs(pwm_a));
    set_pwm_b((uint16_t)abs(pwm_b));
}

void update_pid(error_struct *errors) {
    if (!time_elapsed(last_pid_time, PID_FRAME_INTERVAL)) return;

    last_pid_time = time();
    update_central_error(errors);
    update_motors(get_delta_pwm(errors));
}
