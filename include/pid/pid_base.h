#ifndef PID_BASE_H
#define PID_BASE_H

#include <stdint.h>

#include "../vision/vision_base.h"

/**
 * @struct ErrorStruct
 * @brief Structure to hold error values for PID control.
 */
typedef struct {
    int8_t error;                 // The current error value.
    int8_t last_error;            // The last error value.
    int8_t filtered_delta_error;  // The filtered delta error value.
    int16_t error_sum;            // The sum of errors.
    uint8_t error_weight;         // The weight of the error for PID control.
    int8_t max_error;             // Maximum error value.
    int8_t min_error;             // Minimum error value.
    int8_t max_error_sum;         // Maximum error sum value.
    int8_t min_error_sum;         // Minimum error sum value.
    int8_t error_sum_threshold;   // Threshold for integral calculation.
    SensorState* sensors;         // Pointer to sensor state information.
} ErrorStruct;

/**
 * @struct PidStruct
 * @brief Structure to hold PID control parameters and state.
 */
typedef struct {
    uint8_t kp;              // Proportional gain
    uint8_t ki;              // Integral gain
    uint8_t kd;              // Derivative gain
    uint8_t base_pwm;        // Base PWM value for the motors
    uint8_t max_pwm;         // Maximum PWM value for the motors
    uint8_t min_pwm;         // Minimum PWM value for the motors
    uint8_t frame_interval;  // PID frame interval in centiseconds
    uint16_t last_pid_time;  // Last time the PID was updated
    uint8_t stop_time;       // Time to stop the motors in centiseconds
    ErrorStruct* errors;     // Pointer to the error structure
} PidStruct;

#endif  // PID_BASE_H
