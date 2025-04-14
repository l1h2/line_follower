#ifndef PID_H
#define PID_H

#include <stdint.h>

#define KP 25  // Proportional gain
#define KI 0   // Integral gain
#define KD 0   // Derivative gain

#define ERROR_WEIGHT 2  // Weight for error calculation

// Average error value
#define AVG_ERROR ((ERROR_WEIGHT * (TOTAL_CENTRAL_SENSORS - 1)) / 2)

// Maximum error value
#define ERROR_MAX (TOTAL_CENTRAL_SENSORS - 1) * ERROR_WEIGHT
#define ERROR_MIN (-ERROR_MAX)  // Minimum error value

/**
 * @struct error_struct
 * @brief Structure to hold error values for PID control.
 */
typedef struct {
    int8_t error;
    int8_t last_error;
    int8_t error_sum;
    uint8_t central_sensors_state;
} error_struct;

/**
 * @brief Initializes the PID controller and all related registers.
 */
void pid_init(void);

/**
 * @brief Updates the central error components of the error struct.
 * @param errors Pointer to the error_struct to be updated.
 */
void update_central_error(error_struct *errors);

/**
 * @brief Calculates the delta PWM value based on the error struct.
 * @param errors Pointer to the error_struct containing error values.
 * @return The calculated delta PWM value.
 */
int16_t get_delta_pwm(error_struct *errors);

/**
 * @brief Updates the motor PWM values based on the delta PWM value.
 * @param delta_pwm The delta PWM value to be applied to the motors.
 */
void update_motors(int16_t delta_pwm);

/**
 * @brief Updates the PID controller with the current error values.
 * @param errors Pointer to the error_struct containing error values.
 */
void update_pid(error_struct *errors);

#endif  // PID_H
