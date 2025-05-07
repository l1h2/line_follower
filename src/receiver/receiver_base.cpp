#include "../../include/receiver/receiver_base.h"

#include "../../include/hal/usart.h"

static bool receiver_enabled = false;

void receiver_init(void) {
    if (receiver_enabled) return;

    usart_init_receiver();
    receiver_enabled = true;
}

char read_transmission(void) { return usart_read_char(); }

void read_buffer(char *buffer_out, const uint8_t size) {
    usart_read_buffer(buffer_out, size);
}

bool read_available(void) { return usart_is_data_received(); }

bool read_buffer_full(void) { return usart_is_buffer_full(); }

char read_char(void) {
    while (!usart_is_data_received());
    return usart_read_char();
}

void read(char *buffer_out, const uint8_t chars) {
    uint8_t i = 0;

    for (i = 0; i < chars - 1; i++) {
        buffer_out[i] = read_char();

        if (buffer_out[i] == '\n') break;
    }

    buffer_out[i + 1] = '\0';
}
