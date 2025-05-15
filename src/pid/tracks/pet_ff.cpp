#include "../../../include/pid/tracks/pet_ff.h"

#include "../../../include/vision/track.h"

const static TrackCounters* track = get_counters();
static uint8_t last_section = 0;

int8_t get_pet_feed_forward(void) {
    switch (track->section) {
        case 0:
            return 0;
        case 1:
            return 0;
        case 2:
            return track->section == last_section ? 0 : -4;
            break;
        case 3:
            return 0;
    }
}
