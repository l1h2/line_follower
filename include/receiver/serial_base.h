#ifndef SERIAL_BASE_H
#define SERIAL_BASE_H

#include <stdint.h>

/**
 * @enum SerialCommands
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
    INVALID_COMMAND = 0
} SerialCommands;

/**
 * @struct Command
 * @brief Struct for serial input commands and their values.
 */
typedef struct {
    SerialCommands command;
    uint8_t value;
} Command;

/**
 * @brief Reads the command from the serial buffer.
 * @return The command read from the serial buffer.
 */
Command read_command(void);

/**
 * @brief Waits for a command to be received from the serial buffer.
 * @return The command received from the serial buffer.
 * @note This function will block until a command is received.
 */
Command wait_for_command(void);

#endif  // SERIAL_BASE_H
