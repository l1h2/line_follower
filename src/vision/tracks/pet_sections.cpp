#include "../../../include/vision/tracks/pet_sections.h"

#include "../../../include/timer/time.h"

#define CURVE_1_ACCELERATION_TIME 500

static bool started_curve_1 = false;
static uint32_t curve_1_time;

uint8_t get_pet_track_section(const TrackCounters *track, const bool started) {
    if (!started && track->marker_counter == 1) return 1;

    if (track->crossing_counter == 0 && track->curve_counter == 1) return 2;

    if (track->crossing_counter >= 1) return 3;

    return 0;
}
