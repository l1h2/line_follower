#include "../../include/receiver/serial_base.h"

#include "../../include/hal/usart.h"

#define COMMAND_BUFFER_SIZE 2

static char command_buffer[COMMAND_BUFFER_SIZE];

static SerialCommands get_serial_command(void) {
    SerialCommands serial_command = (SerialCommands)command_buffer[0];

    switch (serial_command) {
        case START:
        case STOP:
        case SET_KP:
        case SET_KI:
        case SET_KD:
        case SET_KFF:
        case SET_KB:
        case SET_BASE_PWM:
        case SET_MAX_PWM:
        case SET_RUNNING_MODE:
        case SET_STOP_MODE:
        case SET_LAPS:
        case SET_STOP_TIME:
        case SET_LOG_DATA:
            return serial_command;
        default:
            return INVALID_COMMAND;
    }
}

static uint8_t get_command_value(void) { return command_buffer[1]; }

Command read_command(void) {
    Command command = {INVALID_COMMAND, 0};

    if (usart_data_available() < COMMAND_BUFFER_SIZE) return command;

    usart_read_buffer(command_buffer, COMMAND_BUFFER_SIZE);

    command.command = get_serial_command();
    command.value = get_command_value();

    return command;
}

Command wait_for_command(void) {
    while (usart_data_available() < COMMAND_BUFFER_SIZE);
    return read_command();
}
