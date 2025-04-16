#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/**
 * @brief Initializes the timer for system time tracking.
 */
void timer_init(void);

/**
 * @brief Returns the current system time in deciseconds.
 *
 * @return The current system time in deciseconds.
 * @note Overflows at 65535 deciseconds (approximately 1.82 hours).
 * @note Uses atomic access to ensure thread safety.
 */
uint16_t get_system_time(void);

#endif  // TIMER_H
