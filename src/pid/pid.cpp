#include "../../include/pid/pid.h"

#include <stdlib.h>

#include "../../include/config.h"
#include "../../include/hal/pwm.h"
#include "../../include/pid/errors.h"
#include "../../include/timer/time.h"
#include "../../include/vision/vision.h"

#define KP 16           // Proportional gain
#define KI 0            // Integral gain
#define KD 1000         // Derivative gain
#define INITIAL_PWM 70  // Initial PWM value to avoid acceleration issues
#define BASE_PWM 90     // Base PWM value for the motors
#define PID_FRAME_INTERVAL 1 * TIME_MULTIPLIER  // PID frame interval

static PidStruct pid = {
    .kp = KP,
    .ki = KI,
    .kd = KD,
    .base_pwm = BASE_PWM,
    .current_pwm = INITIAL_PWM < BASE_PWM ? INITIAL_PWM : BASE_PWM,
    .max_pwm = MAX_PWM,
    .min_pwm = -MAX_PWM,
    .frame_interval = PID_FRAME_INTERVAL,
    .last_pid_time = 0,
    .errors = get_errors(),
};

static int16_t get_p(void) {
    if (pid.kp == 0) return 0;

    return pid.kp * pid.errors->error;
}

static int16_t get_i(void) {
    if (pid.ki == 0) return 0;

    return pid.ki * pid.errors->error_sum * pid.frame_interval;
}

static int16_t get_d(void) {
    if (pid.kd == 0) return 0;

    return pid.kd * pid.errors->filtered_delta_error / pid.frame_interval;
}

static int16_t get_delta_pwm(void) {
    int16_t delta_pwm = 0;

    delta_pwm += get_p();
    delta_pwm += get_i();
    delta_pwm += get_d();

    return delta_pwm;
}

static int16_t get_pwm(const int16_t delta_pwm) {
    int16_t pwm = pid.current_pwm + delta_pwm;

    if (pwm > pid.max_pwm) {
        return pid.max_pwm;
    } else if (pwm < -pid.max_pwm) {
        return -pid.max_pwm;
    }

    return pwm;
}

static void update_motors(const int16_t delta_pwm) {
    const int16_t pwm_a = get_pwm(delta_pwm);
    const int16_t pwm_b = get_pwm(-delta_pwm);

    set_motor_a_dir(pwm_a > 0);
    set_motor_b_dir(pwm_b > 0);

    set_pwm_a((uint16_t)abs(pwm_a));
    set_pwm_b((uint16_t)abs(pwm_b));
}

void pid_init(void) {
    sensors_init();
    motor_setup();
}

bool update_pid(void) {
    if (!time_elapsed(pid.last_pid_time, pid.frame_interval)) return false;

    pid.last_pid_time = time();
    update_errors();
    update_motors(get_delta_pwm());
    return true;
}

PidStruct* get_pid(void) { return &pid; }

void set_kp(const uint8_t kp) { pid.kp = kp; }

void set_ki(const uint8_t ki) { pid.ki = ki; }

void set_kd(const uint8_t kd) { pid.kd = kd == 255 ? 1000 : kd; }

void set_base_pwm(const uint8_t pwm) {
    if (pwm >= pid.max_pwm) {
        pid.base_pwm = pid.max_pwm;
    } else if (pwm <= MIN_PWM) {
        pid.base_pwm = MIN_PWM;
    } else {
        pid.base_pwm = pwm;
    }

    pid.current_pwm = pid.base_pwm;
}

void set_current_pwm(const int16_t pwm) {
    if (pwm >= pid.max_pwm) {
        pid.current_pwm = pid.max_pwm;
    } else if (pwm <= pid.min_pwm) {
        pid.current_pwm = pid.min_pwm;
    } else {
        pid.current_pwm = pwm;
    }
}

void reset_pwm(void) { pid.current_pwm = pid.base_pwm; }

void restart_pwm(void) {
    pid.current_pwm = INITIAL_PWM < pid.base_pwm ? INITIAL_PWM : pid.base_pwm;
}

void set_max_pwm(const uint8_t pwm) {
    if (pwm > MAX_PWM) {
        pid.max_pwm = MAX_PWM;
    } else if (pwm < MIN_PWM) {
        pid.max_pwm = MIN_PWM;
    } else {
        pid.max_pwm = pwm;
    }

    pid.min_pwm = -pid.max_pwm;
}
