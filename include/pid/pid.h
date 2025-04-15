#ifndef PID_H
#define PID_H

#include <stdint.h>

#define KP 25  // Proportional gain
#define KI 0   // Integral gain
#define KD 0   // Derivative gain

#define PID_FRAME_INTERVAL 1          // PID frame interval in deciseconds
#define MAX_ERROR_SUM 127             // Maximum error sum value
#define MIN_ERROR_SUM -MAX_ERROR_SUM  // Minimum error sum value
#define ERROR_SUM_THRESHOLD 5  // Error sum threshold for integral calculation
#define ERROR_WEIGHT 2         // Weight for error calculation

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
    int8_t error;       // The current error value.
    int8_t last_error;  // The last error value for derivative calculation.
    int8_t filtered_delta_error;  // The filtered delta error value.
    int16_t error_sum;            // The sum of errors for integral calculation.
    uint8_t central_sensors_state;  // The state of the central sensors.
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
 * @brief Calculates the proportional component of the PID controller.
 * @param errors Pointer to the error_struct containing error values.
 * @return The calculated proportional component.
 */
int16_t get_p(error_struct *errors);

/**
 * @brief Calculates the integral component of the PID controller.
 * @param errors Pointer to the error_struct containing error values.
 * @return The calculated integral component.
 */
int16_t get_i(error_struct *errors);

/**
 * @brief Calculates the derivative component of the PID controller.
 * @param errors Pointer to the error_struct containing error values.
 * @return The calculated derivative component.
 */
int16_t get_d(error_struct *errors);

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
