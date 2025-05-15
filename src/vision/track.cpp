#include "../../include/vision/track.h"

#include "../../include/logger/logger.h"
#include "../../include/timer/time.h"
#include "../../include/vision/observer.h"
#include "../../include/vision/track_mapping.h"
#include "../../include/vision/vision_base.h"

#define MEMORY_COUNTER_THRESHOLD 8  // Number of consecutive measurements needed
#define CROSSING_COUNTER_THRESHOLD 1  // Threshold for crossing memory counters

static TrackCounters track = {0};
static uint32_t last_true_check_time = 0;

typedef enum { NONE, CROSSING, CURVE, MARKER } MemoryCounters;
static struct {
    uint8_t counter;
    MemoryCounters last;
    bool started;
} memory = {0, NONE, false};

static void reset_memory(void) {
    memory.counter = 0;
    memory.last = NONE;
    memory.started = false;
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
    track.section = 0;
    track.laps = 0;

    reset_memory();
}

static void complete_lap(void) {
    track.laps++;
    track.line_counter = 0;
    track.straight_counter = 0;
    track.crossing_counter = 0;
    track.curve_counter = 0;
    track.marker_counter = 0;
    track.lost_left_counter = 0;
    track.lost_right_counter = 0;
    track.pitch_counter = 0;
    track.section = 0;

    reset_memory();
}

const TrackCounters* get_counters(void) { return &track; }

bool check_start_marker(void) {
    if (!check_marker()) return false;

    track.marker_counter++;

    return (track.marker_counter & 0);
}

static bool check_memory(const MemoryCounters counter_type) {
    if (counter_type != memory.last) {
        memory.last = counter_type;
        memory.counter = 1;
        return false;
    }

    memory.counter++;

    if (counter_type == CROSSING) {
        if (memory.counter < CROSSING_COUNTER_THRESHOLD) return false;
    } else {
        if (memory.counter < MEMORY_COUNTER_THRESHOLD) return false;
    }

    reset_memory();
    return true;
}

static void update_section(void) {
    track.section = get_section(&track, memory.started);

    if (!memory.started && track.section) {
        memory.started = true;
    } else if (track.marker_counter >= 2) {
        complete_lap();
    }
}

static bool process_event(const MemoryCounters counter_type) {
    if (!check_memory(counter_type)) return false;

    last_true_check_time = time();

    switch (counter_type) {
        case CROSSING:
            track.crossing_counter++;
            // debug_print_string("C ");
            break;
        case CURVE:
            track.curve_counter++;
            // debug_print_string("V ");
            break;
        case MARKER:
            track.marker_counter++;
            // debug_print_string("M ");
            break;
        default:
            return false;
    }

    update_section();
    // debug_print_forward_sensors();
    return true;
}

bool update_track_counters(void) {
    if (!time_elapsed(last_true_check_time, DETECTION_DEBOUNCE_TIME)) {
        return false;
    }

    if (check_non_contiguous_sensors()) return false;

    if (check_crossing() && process_event(CROSSING)) return true;
    if (check_curve() && process_event(CURVE)) return true;
    if (check_marker() && process_event(MARKER)) return true;

    return false;
}
