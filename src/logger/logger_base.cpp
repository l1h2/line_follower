#include "../../include/logger/logger_base.h"

#include "../../include/hal/usart.h"

static bool is_logging_enabled = false;

void logger_init(void) {
    if (is_logging_enabled) return;

    usart_init();

    print("Logger Initialized");
    print("******************************************");
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

void print_word(const uint16_t word) {
    usart_transmit('0' + (word / 10000));        // Ten-thousands
    usart_transmit('0' + ((word / 1000) % 10));  // Thousands
    usart_transmit('0' + ((word / 100) % 10));   // Hundreds
    usart_transmit('0' + ((word / 10) % 10));    // Tens
    usart_transmit('0' + (word % 10));           // Ones
}

void print_signed_word(int16_t word) {
    if (word & (1 << 15)) {
        usart_transmit('-');
        word = ~word + 1;  // Convert to positive using two's complement
    }
    print_word(word);
}

void print_binary(const uint8_t byte) {
    for (int8_t i = 7; i >= 0; i--) {
        usart_transmit((byte & (1 << i)) ? '1' : '0');
    }
}

void print_bool(const bool value) { usart_transmit(value ? '1' : '0'); }

void print_string(const char *str) {
    while (*str) {
        usart_transmit(*str++);
    }
}

void print(const char *str) {
    print_string(str);
    print_string("\r\n");
}
