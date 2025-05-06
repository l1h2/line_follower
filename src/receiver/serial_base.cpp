#include "../../include/receiver/serial_base.h"

#include "../../include/hal/usart.h"

#define SERIAL_BUFFER_SIZE RX_BUFFER_SIZE

static char serial_buffer[SERIAL_BUFFER_SIZE];

static SerialCommands get_serial_command(void) {
    SerialCommands serial_command = (SerialCommands)serial_buffer[0];
    switch (serial_command) {
        case START:
        case STOP:
        case SET_KP:
        case SET_KI:
        case SET_KD:
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

static uint8_t get_command_value(void) { return serial_buffer[1]; }

Command read_command(void) {
    Command command = {INVALID_COMMAND, 0};

    if (!usart_is_buffer_full()) return command;

    usart_read_buffer(serial_buffer);

    command.command = get_serial_command();
    command.value = get_command_value();

    return command;
}

Command wait_for_command(void) {
    while (!usart_is_buffer_full());
    return read_command();
}
