#include "../../include/vision/track_mapping.h"

#include "../../include/vision/tracks/rsm_sections.h"

uint8_t get_section(const TrackCounters *track, const bool started) {
#if SELECTED_TRACK == PET
    return 0;
#elif SELECTED_TRACK == RSM
    return get_rsm_track_section(track, started);
#elif SELECTED_TRACK == RIW
    return 0;
#else
    return 0;
#endif
}
