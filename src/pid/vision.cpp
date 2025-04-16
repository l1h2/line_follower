#include "../../include/pid/vision.h"

#include "../../include/hal/sensors.h"
#include "../../include/logger/logger_debug.h"

static TrackingCounters track;

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

void update_counters(const ErrorStruct *errors) {
    if (check_line(errors)) track.line_counter++;
    if (check_straight(errors)) track.straight_counter++;
    if (check_crossing(errors)) track.crossing_counter++;
    if (check_curve(errors)) track.curve_counter++;
    if (check_marker(errors)) track.marker_counter++;
    if (check_lost(errors)) track.lost_counter++;
    if (check_pitch(errors)) track.pitch_counter++;
}

void reset_counters() {
    track.line_counter = 0;
    track.straight_counter = 0;
    track.crossing_counter = 0;
    track.curve_counter = 0;
    track.marker_counter = 0;
    track.lost_counter = 0;
    track.pitch_counter = 0;
}

TrackingCounters get_counters() { return track; }

bool check_stop(const ErrorStruct *errors, const uint8_t laps) {
    static uint16_t debounce_timer = 0;

    if (debounce_timer > 0) {
        print_debounce(debounce_timer);
        debounce_timer--;
        // Ultra-low overhead delay to save machine cycles
        // Each nop takes 1 cycle, so 16 take 1 us at 16 MHz
        // This is a workaround for the debounce timer
        // to avoid using a delay function that takes more time
        // and is not needed in this case
        // Maybe just remove it entirely?
        // Or change system timer resolution from ds to cs or ms?
        __asm__ __volatile__(
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t");
        return false;
    }

    if (!check_marker(errors)) return false;

    track.marker_counter++;
    debounce_timer = DETECTION_DEBOUNCE_TIME;

    return ((track.marker_counter >> 1) >= laps);
}
