#ifndef TIME_H
#define TIME_H

#include <stdint.h>

/**
 * @brief Initializes the timer for system time tracking.
 *
 * This function sets up the timer to generate interrupts at regular intervals,
 * allowing the system to keep track of time in deciseconds.
 */
void start_timer(void);

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

#endif  // TIME_H