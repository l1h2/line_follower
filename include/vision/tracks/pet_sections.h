#ifndef PET_SECTIONS_H
#define PET_SECTIONS_H

#include <stdbool.h>
#include <stdint.h>

#include "../vision_base.h"

/**
 * @brief Get the pet track section
 *
 * @param track The track counters
 * @param started True if the track has started
 * @return uint8_t The track section
 */
uint8_t get_pet_track_section(const TrackCounters *track, const bool started);

#endif  // PET_SECTIONS_H
