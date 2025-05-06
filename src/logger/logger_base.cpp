#include "../../include/logger/logger_base.h"

#include "../../include/hal/usart.h"

static bool logging_enabled = false;

void logger_init(void) {
    if (logging_enabled) return;

    usart_init_transmitter();

    print("Logger Initialized");
    print("******************************************");
    logging_enabled = true;
}

void print_char(const char c) { usart_transmit(c); }

void print_bit(const uint8_t bit_position, const uint8_t byte) {
    if (bit_position > 7) return;  // Invalid bit position

    usart_transmit((byte & (1 << bit_position)) ? '1' : '0');
}

void print_byte(const uint8_t byte) {
    uint8_t temp = byte;

    // Calculate the hundreds digit
    if (temp >= 200) {
        usart_transmit('2');
        temp -= 200;
    } else if (temp >= 100) {
        usart_transmit('1');
        temp -= 100;
    } else {
        usart_transmit('0');
    }

    // Calculate the tens digit
    if (temp >= 90) {
        usart_transmit('9');
        temp -= 90;
    } else if (temp >= 80) {
        usart_transmit('8');
        temp -= 80;
    } else if (temp >= 70) {
        usart_transmit('7');
        temp -= 70;
    } else if (temp >= 60) {
        usart_transmit('6');
        temp -= 60;
    } else if (temp >= 50) {
        usart_transmit('5');
        temp -= 50;
    } else if (temp >= 40) {
        usart_transmit('4');
        temp -= 40;
    } else if (temp >= 30) {
        usart_transmit('3');
        temp -= 30;
    } else if (temp >= 20) {
        usart_transmit('2');
        temp -= 20;
    } else if (temp >= 10) {
        usart_transmit('1');
        temp -= 10;
    } else {
        usart_transmit('0');
    }

    // Calculate the ones digit
    usart_transmit('0' + temp);
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

void print_reverse_binary(const uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        usart_transmit((byte & (1 << i)) ? '1' : '0');
    }
}

void print_bool(const bool value) { usart_transmit(value ? '1' : '0'); }

void print_string(const char *str) {
    while (*str) usart_transmit(*str++);
}

void print_new_line(void) {
    usart_transmit('\r');
    usart_transmit('\n');
}

void print(const char *str) {
    print_string(str);
    print_new_line();
}
