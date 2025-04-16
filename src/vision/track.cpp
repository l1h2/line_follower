#include "../../include/vision/track.h"

#include "../../include/timer/time.h"
#include "../../include/vision/observer.h"

static TrackCounters track = {0};
static uint16_t last_curve_check_time = 0;
static uint16_t last_marker_check_time = 0;

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

TrackCounters get_counters() { return track; }

bool check_break(const ErrorStruct *errors) {
    if (!time_elapsed(last_curve_check_time, DETECTION_DEBOUNCE_TIME))
        return false;

    if (!check_curve(errors)) return false;

    last_curve_check_time = time();
    track.curve_counter++;

    return true;
}

bool check_stop(const ErrorStruct *errors, const uint8_t laps) {
    if (!time_elapsed(last_marker_check_time, DETECTION_DEBOUNCE_TIME))
        return false;

    if (!check_marker(errors)) return false;

    last_marker_check_time = time();
    track.marker_counter++;

    return ((track.marker_counter >> 1) >= laps);
}
