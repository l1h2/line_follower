#ifndef BATTERY_H
#define BATTERY_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initialize the battery monitor.
 */
void battery_monitor_init(void);

/**
 * @brief Enable the battery monitor.
 */
void enable_battery_monitor(void);

/**
 * @brief Disable the battery monitor.
 */
void disable_battery_monitor(void);

/**
 * @brief Get the current battery value.
 * @return The battery value (0-255).
 */
uint8_t get_battery_value(void);

/**
 * @brief Check if the battery is low.
 * @return True if the battery is low, false otherwise.
 */
bool is_battery_low(void);

#endif  // BATTERY_H
