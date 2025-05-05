#include "../../include/hal/pwm.h"

static bool pwm_initialized = false;

void pwm_init(void) {
    if (pwm_initialized) return;

    DDRB |= (1 << PWMA) | (1 << PWMB);

    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << CS10);

    TCNT1 = 0;

    pwm_initialized = true;
}

void motor_setup(void) {
    pwm_init();
    MOTOR_DDR |= ((1 << AIN1) | (1 << AIN2) | (1 << BIN1) | (1 << BIN2));
}

void set_pwm_a(uint16_t pwm) {
    if (pwm > MAX_PWM) pwm = MAX_PWM;
    if (pwm < MIN_PWM) pwm = MIN_PWM;

    MOTOR_A_PWM = pwm;
}

void set_pwm_b(uint16_t pwm) {
    if (pwm > MAX_PWM) pwm = MAX_PWM;
    if (pwm < MIN_PWM) pwm = MIN_PWM;

    MOTOR_B_PWM = pwm;
}

void set_motor_a_dir(const bool dir) {
    if (!dir) {  // Motor A has an inverted connection
        MOTOR_PORT |= (1 << AIN1);
        MOTOR_PORT &= ~(1 << AIN2);
    } else {
        MOTOR_PORT |= (1 << AIN2);
        MOTOR_PORT &= ~(1 << AIN1);
    }
}

void set_motor_b_dir(const bool dir) {
    if (dir) {
        MOTOR_PORT |= (1 << BIN2);
        MOTOR_PORT &= ~(1 << BIN1);
    } else {
        MOTOR_PORT |= (1 << BIN1);
        MOTOR_PORT &= ~(1 << BIN2);
    }
}
