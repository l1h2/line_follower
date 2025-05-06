#include "../../include/pid/mapped_ff.h"

#include "../../include/pid/tracks/rsm_ff.h"
#include "../../include/vision/track.h"

int8_t get_feed_forward(void) {
#if SELECTED_TRACK == PET
    return 0;
#elif SELECTED_TRACK == RSM
    return get_rsm_feed_forward();
#elif SELECTED_TRACK == RIW
    return 0;
#else
    return 0;
#endif
}
