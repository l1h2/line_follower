#include "../../include/vision/observer.h"

bool check_line(const ErrorStruct *errors) {
    return (errors->error > MIN_ERROR && errors->error < MAX_ERROR);
}

bool check_straight(const ErrorStruct *errors) {
    return (errors->error == 0 && errors->sensors.central_sensor &&
            errors->sensors.middle_sensor);
}

bool check_crossing(const ErrorStruct *errors) {
    uint8_t total_central_sensors = 0;

    if (errors->sensors.central_sensor) total_central_sensors++;

    for (uint8_t i = 0; i < 8; i++) {
        if (errors->sensors.central_sensors_state & (1 << i)) {
            total_central_sensors++;
        }
    }

    return (total_central_sensors >= CROSSING_SENSORS_THRESHOLD);
}

bool check_curve(const ErrorStruct *errors) {
    if (!errors->sensors.left_sensor) return false;
    if (errors->sensors.right_sensor) return false;
    if (errors->error <= MIN_ERROR) return false;
    if (check_crossing(errors)) return false;

    return true;
}

bool check_marker(const ErrorStruct *errors) {
    if (!errors->sensors.right_sensor) return false;
    if (errors->sensors.left_sensor) return false;
    if (errors->error >= MAX_ERROR) return false;
    if (check_crossing(errors)) return false;

    return true;
}

bool check_lost(const ErrorStruct *errors) {
    return (!errors->sensors.central_sensors_state &&
            !errors->sensors.central_sensor);
}

bool check_lost_left(const ErrorStruct *errors) {
    if (errors->sensors.right_sensor) return false;
    if (!check_lost(errors)) return false;

    return (errors->error <= MIN_ERROR);
}

bool check_lost_right(const ErrorStruct *errors) {
    if (errors->sensors.left_sensor) return false;
    if (!check_lost(errors)) return false;

    return (errors->error >= MAX_ERROR);
}

bool check_pitch(const ErrorStruct *errors) {
    if (errors->sensors.right_sensor) return false;
    if (errors->sensors.left_sensor) return false;
    if (!check_lost(errors)) return false;

    return (errors->error > MIN_ERROR && errors->error < MAX_ERROR);
}
