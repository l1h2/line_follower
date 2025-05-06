#ifndef RSM_SECTIONS_H
#define RSM_SECTIONS_H

#include <stdbool.h>
#include <stdint.h>

#include "../vision_base.h"

/**
 * @brief Get the rsm track section
 *
 * @param track The track counters
 * @param started True if the track has started
 * @return uint8_t The track section
 */
uint8_t get_rsm_track_section(const TrackCounters *track, const bool started);

#endif  // RSM_SECTIONS_H
