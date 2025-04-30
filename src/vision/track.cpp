#include "../../include/vision/track.h"

#include "../../include/timer/time.h"
#include "../../include/vision/observer.h"

static TrackCounters track = {0};
static uint32_t last_check_time = 0;

void update_counters(void) {
    if (check_line()) track.line_counter++;
    if (check_straight()) track.straight_counter++;
    if (check_crossing()) track.crossing_counter++;
    if (check_curve()) track.curve_counter++;
    if (check_marker()) track.marker_counter++;
    if (check_lost_left()) track.lost_left_counter++;
    if (check_lost_right()) track.lost_right_counter++;
    if (check_pitch()) track.pitch_counter++;
}

void reset_counters(void) {
    track.line_counter = 0;
    track.straight_counter = 0;
    track.crossing_counter = 0;
    track.curve_counter = 0;
    track.marker_counter = 0;
    track.lost_left_counter = 0;
    track.lost_right_counter = 0;
    track.pitch_counter = 0;
}

TrackCounters get_counters(void) { return track; }

bool check_on_crossing(void) {
    if (!time_elapsed(last_check_time, DETECTION_DEBOUNCE_TIME)) return false;
    if (!check_crossing()) return false;

    last_check_time = time();
    track.crossing_counter++;

    return true;
}

bool check_break(void) {
    if (!time_elapsed(last_check_time, DETECTION_DEBOUNCE_TIME)) return false;
    if (!check_on_crossing()) return false;
    if (!check_curve()) return false;

    last_check_time = time();
    track.curve_counter++;

    return true;
}

bool check_start_marker(void) {
    if (!check_marker()) return false;

    track.marker_counter++;

    return (track.marker_counter & 0);
}

bool check_stop_marker(void) {
    if (!time_elapsed(last_check_time, DETECTION_DEBOUNCE_TIME)) return false;
    if (!check_on_crossing()) return false;
    if (!check_marker()) return false;

    last_check_time = time();
    track.marker_counter++;

    return !(track.marker_counter & 1);
}
