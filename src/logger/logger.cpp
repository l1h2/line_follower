#include "../../include/logger/logger.h"

#include "../../include/hal/sensors.h"
#include "../../include/hal/timer.h"
#include "../../include/hal/usart.h"

static uint16_t last_log_time = 0;

void logger_init(void) {
    usart_init();

    print("Logger Initialized");
    print("******************************************");
}

void print_string(const char *str) {
    while (*str) {
        usart_transmit(*str++);
    }
}

void print(const char *str) {
    print_string(str);
    print_string("\r\n");
}

void print_bit(const uint8_t bit_position, const uint8_t byte) {
    if (bit_position > 7) return;  // Invalid bit position

    usart_transmit((byte & (1 << bit_position)) ? '1' : '0');
}

void print_byte(const uint8_t byte) {
    usart_transmit('0' + (byte / 100));        // Hundreds
    usart_transmit('0' + ((byte / 10) % 10));  // Tens
    usart_transmit('0' + (byte % 10));         // Ones
}

void print_signed_byte(int8_t byte) {
    if (byte & (1 << 7)) {
        usart_transmit('-');
        byte = ~byte + 1;  // Convert to positive using two's complement
    }
    print_byte(byte);
}

void printWord(const uint16_t word) {
    usart_transmit('0' + (word / 10000));        // Ten-thousands
    usart_transmit('0' + ((word / 1000) % 10));  // Thousands
    usart_transmit('0' + ((word / 100) % 10));   // Hundreds
    usart_transmit('0' + ((word / 10) % 10));    // Tens
    usart_transmit('0' + (word % 10));           // Ones
}

void print_binary(const uint8_t byte) {
    for (int8_t i = 7; i >= 0; i--) {
        usart_transmit((byte & (1 << i)) ? '1' : '0');
    }
}

void print_sensors(void) {
    print_bit(IR1, ~PIN_IR1);
    print_string(" | ");
    print_bit(IR2, ~PIN_IR2);
    print_string(" - ");
    print_bit(IR3, ~PIN_IR3);
    print_string(" - ");
    print_bit(IR4, ~PIN_IR4);
    print_string(" - ");
    print_bit(IR5, ~PIN_IR5);
    print_string(" - ");
    print_bit(IR6, ~PIN_IR6);
    print_string(" - ");
    print_bit(IR8, ~PIN_IR8);
    print_string(" - ");
    print_bit(IR9, ~PIN_IR9);
    print_string(" - ");
    print_bit(IR10, ~PIN_IR10);
    print_string(" - ");
    print_bit(IR11, ~PIN_IR11);
    print_string(" | ");
    print_bit(IR12, ~PIN_IR12);

    print_string("\r\n");
    print_string("                    ");
    print_bit(IR7, ~PIN_IR7);

    print_string("\r\n");
    print_string("******************************************");
    print_string("\r\n");
    print_string("\r\n");
}

void print_errors(const ErrorStruct *errors) {
    print_string("Error byte: ");
    print_binary(errors->sensors.central_sensors_state);
    print_string(" - Error: ");
    print_signed_byte(errors->error);
    print_string("\r\n");
    print_string("\r\n");
}

void print_diagnostics(const ErrorStruct *errors, const uint16_t interval) {
    if (!time_elapsed(last_log_time, interval)) return;

    last_log_time = time();
    print_errors(errors);
    print_sensors();
}

void print_debounce(const uint16_t debounce_timer) {
    print_string("Debounce timer: ");
    printWord(debounce_timer);
    print_string("\r\n");
}
