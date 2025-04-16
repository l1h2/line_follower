#ifndef ERRORS_H
#define ERRORS_H

#include <stdbool.h>
#include <stdint.h>

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
 * @struct sensor_state
 * @brief Structure to hold the state of the sensors.
 */
typedef struct {
    uint8_t central_sensors_state;  // The state of the central sensors.
    bool central_sensor;  // Flag to indicate if the central sensor is active.
    bool left_sensor;     // Flag to indicate if the left sensor is active.
    bool right_sensor;    // Flag to indicate if the right sensor is active.
    bool middle_sensor;   // Flag to indicate if the middle sensor is active.
} SensorState;

/**
 * @struct ErrorStruct
 * @brief Structure to hold error values for PID control.
 */
typedef struct {
    int8_t error;       // The current error value.
    int8_t last_error;  // The last error value for derivative calculation.
    int8_t filtered_delta_error;  // The filtered delta error value.
    int16_t error_sum;            // The sum of errors for integral calculation.
    SensorState sensors;          // Sensor state information.
} ErrorStruct;

/**
 * @brief Updates the sensor states in the error struct.
 * @param errors Pointer to the ErrorStruct to be updated.
 */
void update_sensors(ErrorStruct *errors);

/**
 * @brief Updates the error component of the error struct.
 * @param errors Pointer to the ErrorStruct to be updated.
 */
void update_error(ErrorStruct *errors);

/**
 * @brief Updates the error sum component of the error struct.
 * @param errors Pointer to the ErrorStruct to be updated.
 */
void update_error_sum(ErrorStruct *errors);

/**
 * @brief Updates the last error component of the error struct.
 * @param errors Pointer to the ErrorStruct to be updated.
 */
void update_last_error(ErrorStruct *errors);

/**
 * @brief Updates the delta error component of the error struct.
 * @param errors Pointer to the ErrorStruct to be updated.
 */
void update_delta_error(ErrorStruct *errors);

/**
 * @brief Updates the error struct with the latest sensor data and error values.
 * @param errors Pointer to the ErrorStruct to be updated.
 */
void update_error_struct(ErrorStruct *errors);

#endif  // ERRORS_H
