#ifndef ERRORS_H
#define ERRORS_H

#include <stdint.h>

#include "../vision/vision.h"

#define ERROR_WEIGHT 2  // Weight for error calculation

// Average error value
#define AVG_ERROR ((ERROR_WEIGHT * (TOTAL_CENTRAL_SENSORS - 1)) / 2)

// Maximum error value
#define MAX_ERROR (TOTAL_CENTRAL_SENSORS - 1) * ERROR_WEIGHT - AVG_ERROR
#define MIN_ERROR (-MAX_ERROR)        // Minimum error value
#define MAX_ERROR_SUM 127             // Maximum error sum value
#define MIN_ERROR_SUM -MAX_ERROR_SUM  // Minimum error sum value
#define ERROR_SUM_THRESHOLD 2  // Error sum threshold for integral calculation

/**
 * @struct ErrorStruct
 * @brief Structure to hold error values for PID control.
 */
typedef struct {
    int8_t error;       // The current error value.
    int8_t last_error;  // The last error value for derivative calculation.
    int8_t filtered_delta_error;  // The filtered delta error value.
    int16_t error_sum;            // The sum of errors for integral calculation.
    SensorState* sensors;         // Pointer to sensor state information.
} ErrorStruct;

/**
 * @brief Updates the error struct with the latest sensor data and error values.
 */
void update_errors(void);

/**
 * @brief Clears the error struct by resetting its values.
 */
void clear_errors(void);

/**
 * @brief Returns a pointer to the error struct.
 *
 * @return Pointer to the ErrorStruct containing error values.
 */
ErrorStruct* get_errors(void);

#endif  // ERRORS_H
