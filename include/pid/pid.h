#ifndef PID_H
#define PID_H

#include <stdint.h>

#define KP 10                 // Proportional gain
#define KI 0                  // Integral gain
#define KD 0                  // Derivative gain
#define PID_FRAME_INTERVAL 1  // PID frame interval in centiseconds
#define STOP_TIME 20          // Time to stop the motors in centiseconds
#define BREAK_FRAMES STOP_TIME / PID_FRAME_INTERVAL  // Number of frames to stop

/**
 * @brief Initializes the PID controller and all related registers.
 */
void pid_init(void);

/**
 * @brief Updates the PID controller with the current error values.
 */
void update_pid(void);

/**
 * @brief Gets the base PWM value for the motors.
 * @return The current base PWM value.
 */
uint8_t get_base_pwm(void);

/**
 * @brief Sets the base PWM value for the motors.
 * @param pwm The new base PWM value to be set.
 */
void set_base_pwm(const uint8_t pwm);

#endif  // PID_H
