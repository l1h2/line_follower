#ifndef TIME_H
#define TIME_H

#include <stdint.h>

/**
 * @brief Initializes the timer for system time tracking.
 *
 * This function sets up the timer to generate interrupts at regular intervals,
 * allowing the system to keep track of time in milliseconds.
 */
void start_timer(void);

/**
 * @brief Returns the current system time in milliseconds.
 *
 * @return The current system time in milliseconds.
 * @note Overflows at 65535 milliseconds (approximately 11 minutes).
 */
uint32_t time(void);

/**
 * @brief Checks if the specified time interval has elapsed since the last time.
 *
 * @param last_time The last recorded time in milliseconds.
 * @param interval The time interval to check in milliseconds.
 * @return true if the interval has elapsed, false otherwise.
 */
bool time_elapsed(const uint32_t last_time, const uint32_t interval);

/**
 * @brief Waits for the specified time interval to elapse.
 *
 * @param interval The time interval to wait for in milliseconds.
 */
void wait(const uint32_t interval);

#endif  // TIME_H