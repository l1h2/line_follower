#ifndef BLUETOOTH_BASE_H
#define BLUETOOTH_BASE_H

#include <stdint.h>

#include "../../include/pid/pid.h"
#include "../../include/state_machine/state_machine_base.h"

/**
 * @enum SerialSmOutputs
 * @brief Enum for serial output State Machine commands.
 */
typedef enum {
    STATE,
    RUNNING_MODE,
    STOP_MODE,
    LAPS,
    STOP_TIME,
    LOG_DATA,
} SerialSmOutputs;

/**
 * @enum SerialPidOutputs
 * @brief Enum for serial output PID commands.
 */
typedef enum {
    KP,
    KI,
    KD,
    BASE_PWM,
    MAX_PWM,
} SerialPidOutputs;

/**
 * @brief Send the battery value to the receiver.
 */
void send_battery_value(void);

/**
 * @brief Signal receiver to start listening for binary data.
 */
void send_start_signal(void);

/**
 * @brief Signal receiver to stop listening for binary data.
 */
void send_stop_signal(void);

/**
 * @brief Send information to the receiver.
 * @param sm The state machine structure containing the information to send.
 * @param info The type of information to send.
 */
void send_state_machine_info(const StateMachine *sm,
                             const SerialSmOutputs info);

/**
 * @brief Send information to the receiver.
 * @param The PID structure containing the information to send.
 * @param info The type of information to send.
 */
void send_pid_info(const PidStruct *pid, const SerialPidOutputs info);

#endif  // BLUETOOTH_BASE_H
