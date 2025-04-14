#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

#define PWMA PB1  // PWM output for motor A
#define AIN1 PB3  // First direction control for motor A
#define AIN2 PB0  // Second direction control for motor A
#define BIN1 PB5  // First direction control for motor B
#define BIN2 PB4  // Second direction control for motor B
#define PWMB PB2  // PWM output for motor B

#define MOTOR_A_PWM OCR1B  // PWM register for motor A
#define MOTOR_B_PWM OCR1A  // PWM register for motor B

#define MOTOR_DDR DDRB    // Data Direction Register for motor control
#define MOTOR_PORT PORTB  // Port for motor control

#define BASE_PWM 120       // Base PWM value for motor speed
#define MAX_PWM 255        // Maximum PWM value for motor speed
#define MIN_PWM 0          // Minimum PWM value for motor speed
#define MAX_DELTA_PWM 500  // Maximum change in PWM value

/**
 * @brief Sets up the PWM registers for motor control.
 *
 * This function initializes the PWM registers for controlling two motors.
 *
 * @note The PWM control is set to Fast PWM mode, 8-bit (mode 5), with a 1024
 * pre-scale.
 */
void pwm_init(void);

/**
 * @brief Configures the motor driver pins and initializes the PWM.
 */
void motor_setup(void);

/**
 * @brief Sets the PWM value for motor A.
 *
 * @param pwm The PWM value to set for motor A (0-255).
 */
void set_pwm_a(uint16_t pwm);

/**
 * @brief Sets the PWM value for motor B.
 *
 * @param pwm The PWM value to set for motor B (0-255).
 */
void set_pwm_b(uint16_t pwm);

/**
 * @brief Sets the direction of motor A.
 *
 * @param dir The direction to set for motor A (true for forward, false for
 * backward).
 */
void set_motor_a_dir(const bool dir);

/**
 * @brief Sets the direction of motor B.
 *
 * @param dir The direction to set for motor B (true for forward, false for
 * backward).
 */
void set_motor_b_dir(const bool dir);

#endif  // PWM_H
