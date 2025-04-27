#include "../../include/receiver/receiver_base.h"

#include "../../include/hal/usart.h"

static bool receiver_enabled = false;

void receiver_init(void) {
    if (receiver_enabled) return;

    usart_init_receiver();
    receiver_enabled = true;
}

uint8_t buffer_size(void) { return USART_BUFFER_SIZE; }

char read_last_transmission(void) { return usart_read_last_char(); }

char *read_raw_buffer(char *buffer_out) {
    return usart_read_buffer(buffer_out);
}

bool read_available(void) { return usart_is_data_received(); }

bool read_buffer_full(void) { return usart_is_buffer_full(); }

char read_char(void) {
    while (!usart_is_data_received());
    return read_last_transmission();
}

char *read(char *buffer_out) {
    while (!usart_is_buffer_full());
    return read_raw_buffer(buffer_out);
}
