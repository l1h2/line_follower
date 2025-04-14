#include "../../include/hal/usart.h"

#include <avr/io.h>

static bool usart_initialized = false;

void usart_init(void) {
    if (usart_initialized) return;

    UBRR0H = (uint8_t)(UBRR >> 8);
    UBRR0L = (uint8_t)UBRR;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    usart_initialized = true;
}

void usart_transmit(const uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

char usart_receive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}
