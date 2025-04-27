#ifndef BLUETOOTH_LOGGER_H
#define BLUETOOTH_LOGGER_H

#include "../state_machine/state_machine_base.h"

/**
 * @brief Sends all sensor data optimized for performance.
 */
void send_vision_data(void);

/**
 * @brief Sends all PID data in the bluetooth protocol format.
 */
void send_pid_data(void);

/**
 * @brief Sends all state machine data in the bluetooth protocol format.
 * @param sm Pointer to the state machine structure.
 */
void send_state_machine_data(const StateMachine* sm);

/**
 * @brief Sends all data in the bluetooth protocol format.
 * @param sm Pointer to the state machine structure.
 * @param interval The time interval in centiseconds for printing data.
 * (Default: 100)
 */
void send_robot_data(const StateMachine* sm, const uint16_t interval = 100);

#endif  // BLUETOOTH_LOGGER_H
