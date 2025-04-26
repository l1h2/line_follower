#include "../../include/pid/errors.h"

#include <stdlib.h>

#include "../../include/hal/sensors.h"
#include "../../include/vision/vision.h"

#define ERROR_WEIGHT 2  // Weight for error calculation

// Average error value
#define AVG_ERROR ((ERROR_WEIGHT * (TOTAL_CENTRAL_SENSORS - 1)) / 2)

// Maximum error value
#define MAX_ERROR (TOTAL_CENTRAL_SENSORS - 1) * ERROR_WEIGHT - AVG_ERROR
#define MIN_ERROR (-MAX_ERROR)        // Minimum error value
#define MAX_ERROR_SUM 127             // Maximum error sum value
#define MIN_ERROR_SUM -MAX_ERROR_SUM  // Minimum error sum value
#define ERROR_SUM_THRESHOLD 2  // Error sum threshold for integral calculation

static ErrorStruct errors = {
    .error = 0,
    .last_error = 0,
    .filtered_delta_error = 0,
    .error_sum = 0,
    .error_weight = ERROR_WEIGHT,
    .max_error = MAX_ERROR,
    .min_error = MIN_ERROR,
    .max_error_sum = MAX_ERROR_SUM,
    .min_error_sum = MIN_ERROR_SUM,
    .error_sum_threshold = ERROR_SUM_THRESHOLD,
    .sensors = get_sensors(),
};

static void update_error(void) {
    const uint8_t central_sensors_state = errors.sensors->central_sensors_state;
    if (!central_sensors_state) {
        if (errors.sensors->central_sensor) errors.error = 0;
        return;
    }

    uint8_t count = 0;
    int8_t new_error = 0;

    for (uint8_t i = 0; i <= 7; i++) {
        if (!(central_sensors_state & (1 << i))) continue;

        new_error += i;
        count++;
    }

    errors.error = new_error * ERROR_WEIGHT / count - AVG_ERROR;
}

static void update_error_sum(void) {
    // Test integral windup prevention and faster reseting
    if (errors.error == 0) {  // Maybe use threshold instead of 0
        errors.error_sum = 0;
        return;
    }

    errors.error_sum += errors.error;

    if (errors.error_sum > MAX_ERROR_SUM) {
        errors.error_sum = MAX_ERROR_SUM;
    } else if (errors.error_sum < MIN_ERROR_SUM) {
        errors.error_sum = MIN_ERROR_SUM;
    }
}

static void update_delta_error(void) {
    const int16_t delta_error = errors.error - errors.last_error;

    // Experiment with exponent filtering
    errors.filtered_delta_error =
        (errors.filtered_delta_error * 7 + delta_error) >> 3;
}

static void update_last_error(void) { errors.last_error = errors.error; }

void update_errors(void) {
    update_sensors();
    update_error();
    update_error_sum();
    update_delta_error();
    update_last_error();
}

void clear_errors(void) {
    errors.error = 0;
    errors.last_error = 0;
    errors.filtered_delta_error = 0;
    errors.error_sum = 0;
    clear_sensors();
}

ErrorStruct* get_errors(void) { return &errors; }
