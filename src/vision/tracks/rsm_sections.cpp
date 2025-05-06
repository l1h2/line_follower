#include "../../../include/vision/tracks/rsm_sections.h"

#include "../../../include/timer/time.h"

#define CURVE_1_ACCELERATION_TIME 500

static bool started_curve_1 = false;
static uint32_t curve_1_time;

uint8_t get_rsm_track_section(const TrackCounters *track, const bool started) {
    if (!started && track->marker_counter == 1) return 1;

    if (track->curve_counter == 1) {
        if (!started_curve_1) {
            curve_1_time = time();
            started_curve_1 = true;
            return 2;
        }

        if (!time_elapsed(curve_1_time, CURVE_1_ACCELERATION_TIME)) return 3;

        return 4;
    }

    if (track->crossing_counter == 1) return 5;

    if (track->crossing_counter == 3) return 6;

    if (track->crossing_counter == 4) return 7;

    if (track->crossing_counter == 7) return 8;

    if (track->crossing_counter == 8) return 9;

    if (track->crossing_counter == 11) return 10;

    if (track->crossing_counter == 12) return 11;

    if (track->crossing_counter == 13) return 12;

    if (track->crossing_counter == 14) return 13;

    if (track->crossing_counter == 15) return 14;

    if (track->crossing_counter == 16) return 15;

    if (track->crossing_counter == 19) return 16;

    if (track->crossing_counter == 20) return 17;

    if (track->marker_counter == 2) return 99;
}
