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
 */
uint16_t time(void);

/**
 * @brief Checks if the specified time interval has elapsed since the last time.
 *
 * @param last_time The last recorded time in deciseconds.
 * @param interval The time interval to check in deciseconds.
 * @return true if the interval has elapsed, false otherwise.
 */
bool time_elapsed(const uint16_t last_time, const uint16_t interval);

/**
 * @brief Waits for the specified time interval to elapse.
 *
 * @param interval The time interval to wait for in deciseconds.
 */
void wait(const uint16_t interval);

#endif  // TIMER_H
