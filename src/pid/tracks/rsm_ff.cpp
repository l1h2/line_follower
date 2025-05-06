#include "../../../include/pid/tracks/rsm_ff.h"

#include "../../../include/vision/track.h"

const static TrackCounters* track = get_counters();
static uint8_t last_section = 0;

int8_t get_rsm_feed_forward(void) {
    switch (track->section) {
        case 0:
            return -3;
        case 2:
            return track->section == last_section ? 0 : -2;
            break;
        case 4:
            return -3;
        case 6:
        case 8:
        case 10:
        case 12:
        case 14:
        case 16:
            return track->section == last_section ? 0 : -3;
            break;
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
        case 11:
        case 13:
        case 15:
        case 17:
            return 2;
            break;
    }
}
