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

static volatile char rx_buffer[RX_BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;

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
        tx_tail = (tx_tail + 1) & (TX_BUFFER_SIZE - 1);
    } else {
        UCSR0B &= ~(1 << UDRIE0);
    }
}

void usart_transmit(const uint8_t data) {
    const uint8_t next_head = (tx_head + 1) & (TX_BUFFER_SIZE - 1);

    while (next_head == tx_tail);

    tx_buffer[tx_head] = data;
    tx_head = next_head;

    UCSR0B |= (1 << UDRIE0);
}

ISR(USART_RX_vect) {
    const uint8_t next_head = (rx_head + 1) & (RX_BUFFER_SIZE - 1);

    if (next_head == rx_tail) return;  // Buffer overflow

    rx_buffer[rx_head] = UDR0;
    rx_head = next_head;
}

char usart_read_char(void) {
    char data;
    cli();

    if (rx_head != rx_tail) {
        data = rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1) & (RX_BUFFER_SIZE - 1);
    } else {
        data = 0;
    }

    sei();
    return data;
}

void usart_read_buffer(char *buffer_out, uint8_t size) {
    cli();

    const uint8_t data_size =
        (rx_head - rx_tail + RX_BUFFER_SIZE) & (RX_BUFFER_SIZE - 1);

    if (size > data_size || size == 0) size = data_size;

    for (uint8_t i = 0; i < size; i++) {
        buffer_out[i] = rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1) & (RX_BUFFER_SIZE - 1);
    }

    sei();
}

uint8_t usart_data_available(void) {
    cli();
    const uint8_t available =
        (rx_head - rx_tail + RX_BUFFER_SIZE) & (RX_BUFFER_SIZE - 1);
    sei();
    return available;
}

bool usart_is_data_received(void) {
    cli();
    const bool received = (rx_head != rx_tail);
    sei();
    return received;
}

bool usart_is_buffer_full(void) {
    cli();
    const bool full = ((rx_head + 1) & (RX_BUFFER_SIZE - 1)) == rx_tail;
    sei();
    return full;
}
