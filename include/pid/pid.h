#ifndef PID_H
#define PID_H

#include <stdbool.h>
#include <stdint.h>

#include "pid_base.h"

/**
 * @brief Initializes the PID controller and all related registers.
 */
void pid_init(void);

/**
 * @brief Updates the PID controller with the current error values.
 * @return true if the PID controller was updated, false otherwise.
 */
bool update_pid(void);

/**
 * @brief Returns a pointer to the PID struct.
 * @return Pointer to the PidStruct containing PID parameters and state.
 */
PidStruct* get_pid(void);

/**
 * @brief Set the proportional gain (Kp) value for the PID controller.
 * @param kp The new proportional gain value to be set.
 */
void set_kp(const uint8_t kp);

/**
 * @brief Set the integral gain (Ki) value for the PID controller.
 * @param ki The new integral gain value to be set.
 */
void set_ki(const uint8_t ki);

/**
 * @brief Set the derivative gain (Kd) value for the PID controller.
 * @param kd The new derivative gain value to be set.
 */
void set_kd(const uint8_t kd);

/**
 * @brief Sets the base PWM value for the motors.
 * @param pwm The new base PWM value to be set.
 * @note This function is used for gradually stopping the motors.
 */
void set_base_pwm(const uint8_t pwm);

/**
 * @brief Sets the max PWM value for the motors.
 * @param pwm The new base PWM value to be set.
 * @note This function is used for gradually stopping the motors.
 */
void set_max_pwm(const uint8_t pwm);

#endif  // PID_H
