#ifndef PID_H
#define PID_H

#include <stdint.h>

#include "errors.h"

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
 * @brief Calculates the proportional component of the PID controller.
 * @param errors Pointer to the ErrorStruct containing error values.
 * @return The calculated proportional component.
 */
int16_t get_p(const ErrorStruct *errors);

/**
 * @brief Calculates the integral component of the PID controller.
 * @param errors Pointer to the ErrorStruct containing error values.
 * @return The calculated integral component.
 */
int16_t get_i(const ErrorStruct *errors);

/**
 * @brief Calculates the derivative component of the PID controller.
 * @param errors Pointer to the ErrorStruct containing error values.
 * @return The calculated derivative component.
 */
int16_t get_d(const ErrorStruct *errors);

/**
 * @brief Calculates the delta PWM value based on the error struct.
 * @param errors Pointer to the ErrorStruct containing error values.
 * @return The calculated delta PWM value.
 */
int16_t get_delta_pwm(const ErrorStruct *errors);

/**
 * @brief Updates the motor PWM values based on the delta PWM value.
 * @param delta_pwm The delta PWM value to be applied to the motors.
 */
void update_motors(const int16_t delta_pwm);

/**
 * @brief Updates the PID controller with the current error values.
 * @param errors Pointer to the ErrorStruct containing error values.
 */
void update_pid(ErrorStruct *errors);

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
