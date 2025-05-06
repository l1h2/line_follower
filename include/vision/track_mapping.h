#ifndef TRACK_MAPPING_H
#define TRACK_MAPPING_H

#include <stdbool.h>
#include <stdint.h>

#include "vision_base.h"

/**
 * @brief Gets the section for the current selected track, based on the track's
 * characteristics.
 *
 * @param track The track counters structure containing the current state of the
 * track.
 * @param started A boolean indicating whether the track has started or not.
 * @return uint8_t The section number of the selected track.
 */
uint8_t get_section(const TrackCounters *track, const bool started);

#endif  // TRACK_MAPPING_H
