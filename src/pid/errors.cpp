#include "../../include/pid/errors.h"

#include <stdlib.h>

void update_error(ErrorStruct *errors) {
    const uint8_t central_sensors_state = errors->sensors.central_sensors_state;
    if (!central_sensors_state) {
        if (errors->sensors.central_sensor) errors->error = 0;
        return;
    }

    uint8_t count = 0;
    int8_t new_error = 0;

    for (uint8_t i = 0; i <= 7; i++) {
        if (!(central_sensors_state & (1 << i))) continue;

        new_error += i;
        count++;
    }

    errors->error = new_error * ERROR_WEIGHT / count - AVG_ERROR;
}

void update_error_sum(ErrorStruct *errors) {
    // Test integral windup prevention and faster reseting
    if (errors->error == 0) {  // Maybe use threshold instead of 0
        errors->error_sum = 0;
        return;
    }

    errors->error_sum += errors->error;

    if (errors->error_sum > MAX_ERROR_SUM) {
        errors->error_sum = MAX_ERROR_SUM;
    } else if (errors->error_sum < MIN_ERROR_SUM) {
        errors->error_sum = MIN_ERROR_SUM;
    }
}

void update_delta_error(ErrorStruct *errors) {
    const int16_t delta_error = errors->error - errors->last_error;

    // Experiment with exponent filtering
    errors->filtered_delta_error =
        (errors->filtered_delta_error * 7 + delta_error) >> 3;
}

void update_last_error(ErrorStruct *errors) {
    errors->last_error = errors->error;
}

void update_error_struct(ErrorStruct *errors) {
    update_sensors(&errors->sensors);
    update_error(errors);
    update_error_sum(errors);
    update_delta_error(errors);
    update_last_error(errors);
}
