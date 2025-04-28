#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/**
 * @brief Initializes the timer for system time tracking.
 */
void timer_init(void);

/**
 * @brief Returns the current system time in milliseconds.
 *
 * @return The current system time in milliseconds.
 * @note Uses atomic access to ensure thread safety.
 */
uint32_t get_system_time(void);

#endif  // TIMER_H
