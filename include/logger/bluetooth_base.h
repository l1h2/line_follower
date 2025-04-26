#ifndef BLUETOOTH_BASE_H
#define BLUETOOTH_BASE_H

#include <stdint.h>

#include "../../include/state_machine/state_machine_base.h"

/**
 * @brief Enum for serial input commands.
 */
typedef enum {
    START = '$',
    STOP = '%',
    SET_KP = 'P',
    SET_KI = 'I',
    SET_KD = 'D',
    SET_BASE_PWM = 'B',
    SET_MAX_PWM = 'M',
    SET_RUNNING_MODE = 'R',
    SET_STOP_MODE = 'S',
    SET_LAPS = 'L',
    SET_STOP_TIME = 'T',
} SerialInputs;

typedef enum {
    STATE,
    RUNNING_MODE,
    STOP_MODE,
    LAPS,
    STOP_TIME,
} SerialSmOutputs;

/**
 * @brief Enum for serial output commands.
 */
typedef enum {
    KP,
    KI,
    KD,
    BASE_PWM,
    MAX_PWM,
} SerialPidOutputs;

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
 * @param info The type of information to send.
 * @param value The value associated with the information.
 */
void send_pid_info(const SerialPidOutputs info, const uint8_t value);

#endif  // BLUETOOTH_BASE_H
