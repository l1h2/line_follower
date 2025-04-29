#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/**
 * @brief Initializes the timer for system time tracking.
 * @note Can use either milliseconds or microseconds for time tracking depending
 * if `US_SYSTEM_TIME` is defined in the configs.
 */
void timer_init(void);

/**
 * @brief Initializes the debug timer.
 * @note Can be used to count machine cycles or for debugging purposes.
 */
void debug_timer_init(void);

/**
 * @brief Stops the debug timer.
 */
void debug_timer_stop(void);

/**
 * @brief Returns the current system time.
 *
 * @return The current system time.
 * @note Uses atomic access to ensure thread safety.
 */
uint32_t get_system_time(void);

#endif  // TIMER_H
