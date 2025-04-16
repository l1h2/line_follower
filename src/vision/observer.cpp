#include "../../include/vision/observer.h"

bool check_line(const ErrorStruct *errors) {
    return (errors->error > MIN_ERROR && errors->error < MAX_ERROR);
}

bool check_straight(const ErrorStruct *errors) {
    return (errors->error == 0 && errors->sensors.central_sensor &&
            errors->sensors.middle_sensor);
}

bool check_crossing(const ErrorStruct *errors) {
    // TODO: Add missing checks for crossing detection
    return (errors->sensors.central_sensors_state == 0xFF &&
            errors->sensors.central_sensor && errors->sensors.left_sensor &&
            errors->sensors.right_sensor);
}

bool check_curve(const ErrorStruct *errors) {
    // TODO: Add missing checks for curve detection
    if (!errors->sensors.left_sensor) return false;
    if (check_crossing(errors)) return false;

    return true;
}

bool check_marker(const ErrorStruct *errors) {
    // TODO: Add missing checks for marker detection
    if (!errors->sensors.right_sensor) return false;
    if (check_crossing(errors)) return false;

    return true;
}

bool check_lost(const ErrorStruct *errors) {
    return (!errors->sensors.central_sensors_state &&
            !errors->sensors.central_sensor && errors->error <= MIN_ERROR &&
            errors->error >= MAX_ERROR);
}

bool check_pitch(const ErrorStruct *errors) {
    return (!errors->sensors.central_sensors_state &&
            !errors->sensors.central_sensor && errors->error > MIN_ERROR &&
            errors->error < MAX_ERROR);
}
