#ifndef TIME_H
#define TIME_H

#include <stdint.h>

/**
 * @brief Initializes the timer for system time tracking.
 *
 * This function sets up the timer to generate interrupts at regular intervals,
 * allowing the system to keep track of time.
 */
void start_timer(void);

/**
 * @brief Initializes the debug timer.
 *
 * This function sets up a debug timer that can be used for debugging purposes.
 * It can be used to count machine cycles or for other timing-related tasks.
 */
void start_debug_timer(void);

/**
 * @brief Stops the debug timer.
 *
 * This function stops the debug timer that was previously initialized.
 */
void stop_debug_timer(void);

/**
 * @brief Returns the current system time.
 *
 * @return The current system time.
 * @note Overflows at ~50 days (ms) or ~1.2 hours (us).
 */
uint32_t time(void);

/**
 * @brief Checks if the specified time interval has elapsed since the last time.
 *
 * @param last_time The last recorded time.
 * @param interval The time interval to check.
 * @return true if the interval has elapsed, false otherwise.
 */
bool time_elapsed(const uint32_t last_time, const uint32_t interval);

#endif  // TIME_H
