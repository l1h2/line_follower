#include "../../include/vision/observer.h"

#include <stdlib.h>

#include "../../include/pid/errors.h"
#include "../../include/vision/vision_base.h"

// Minimum number of sensors for crossing detection
#define CROSSING_SENSORS_THRESHOLD 4

// Threshold for max error possible in a side marker detection
#define SIDE_MARKERS_ERROR_THRESHOLD 3

static const ErrorStruct *errors = get_errors();

bool check_non_contiguous_sensors(void) {
    bool found_active = false;
    bool found_gap = false;

    for (uint8_t i = 0; i < 8; i++) {
        if (errors->sensors->central_sensors_state & (1 << i)) {
            if (found_gap) return true;
            found_active = true;
        } else if (found_active) {
            found_gap = true;
        }
    }

    return false;
}

bool check_line(void) {
    return (errors->error > errors->min_error &&
            errors->error < errors->max_error);
}

bool check_straight(void) {
    return (errors->error == 0 && errors->sensors->central_sensor &&
            errors->sensors->middle_sensor);
}

bool check_crossing(void) {
    uint8_t total_central_sensors = 0;

    if (errors->sensors->central_sensor) total_central_sensors++;

    for (uint8_t i = 0; i < 8; i++) {
        if (errors->sensors->central_sensors_state & (1 << i)) {
            total_central_sensors++;
        }
    }

    return (total_central_sensors >= CROSSING_SENSORS_THRESHOLD);
}

bool check_curve(void) {
    if (!errors->sensors->left_sensor) return false;
    if (errors->sensors->right_sensor) return false;
    if ((int8_t)abs(errors->error) > SIDE_MARKERS_ERROR_THRESHOLD) return false;

    return true;
}

bool check_marker(void) {
    if (!errors->sensors->right_sensor) return false;
    if (errors->sensors->left_sensor) return false;
    if ((int8_t)abs(errors->error) > SIDE_MARKERS_ERROR_THRESHOLD) return false;

    return true;
}

bool check_lost(void) {
    return (!errors->sensors->central_sensors_state &&
            !errors->sensors->central_sensor);
}

bool check_lost_left(void) {
    if (errors->sensors->right_sensor) return false;
    if (!check_lost()) return false;

    return (errors->error <= errors->min_error);
}

bool check_lost_right(void) {
    if (errors->sensors->left_sensor) return false;
    if (!check_lost()) return false;

    return (errors->error >= errors->max_error);
}

bool check_pitch(void) {
    if (errors->sensors->right_sensor) return false;
    if (errors->sensors->left_sensor) return false;
    if (!check_lost()) return false;

    return (errors->error > errors->min_error &&
            errors->error < errors->max_error);
}
