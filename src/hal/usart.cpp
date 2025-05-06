#include "../../include/hal/usart.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>

// UBRR value for the desired baud rate
#define UBRR (((F_CPU / 16UL) / BAUD) - 1)

static bool usart_initialized = false;
static bool transmitter_initialized = false;
static bool receiver_initialized = false;

static volatile char tx_buffer[TX_BUFFER_SIZE];
static volatile uint8_t tx_head = 0;
static volatile uint8_t tx_tail = 0;

static volatile char buffer[RX_BUFFER_SIZE];
static volatile uint8_t buffer_index = 0;
static volatile bool data_received = false;

static void usart_init(void) {
    if (usart_initialized) return;

    UBRR0H = (uint8_t)(UBRR >> 8);
    UBRR0L = (uint8_t)UBRR;

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    usart_initialized = true;
}

void usart_init_transmitter(void) {
    if (transmitter_initialized) return;

    usart_init();
    UCSR0B |= (1 << TXEN0) | (1 << UDRIE0);

    transmitter_initialized = true;

    sei();
}

void usart_init_receiver(void) {
    if (receiver_initialized) return;

    usart_init();
    UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);

    receiver_initialized = true;

    sei();
}

ISR(USART_UDRE_vect) {
    if (tx_head != tx_tail) {
        UDR0 = tx_buffer[tx_tail];
        tx_tail = (tx_tail + 1) % TX_BUFFER_SIZE;
    } else {
        UCSR0B &= ~(1 << UDRIE0);
    }
}

void usart_transmit(const uint8_t data) {
    const uint8_t next_head = (tx_head + 1) % TX_BUFFER_SIZE;

    while (next_head == tx_tail);

    tx_buffer[tx_head] = data;
    tx_head = next_head;

    UCSR0B |= (1 << UDRIE0);
}

ISR(USART_RX_vect) {
    buffer[buffer_index++] = UDR0;
    if (buffer_index >= RX_BUFFER_SIZE) buffer_index = 0;
    data_received = true;
}

char usart_read_last_char(void) {
    char data;
    cli();
    const int8_t index =
        buffer_index - 1 < 0 ? RX_BUFFER_SIZE - 1 : buffer_index - 1;
    data = buffer[index];
    data_received = false;
    sei();
    return data;
}

char *usart_read_buffer(char *buffer_out) {
    cli();
    for (uint8_t i = 0; i < RX_BUFFER_SIZE; i++) {
        buffer_out[i] = buffer[i];
        buffer[i] = 0;
    }
    buffer_index = 0;
    data_received = false;
    sei();
    return buffer_out;
}

bool usart_is_data_received(void) {
    bool received;
    cli();
    received = data_received;
    sei();
    return received;
}

bool usart_is_buffer_full(void) {
    bool full;
    cli();
    full = buffer_index == 0 && data_received;
    sei();
    return full;
}
