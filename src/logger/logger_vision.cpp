#include "../../include/logger/logger_vision.h"

#include <stdint.h>

#include "../../include/hal/usart.h"
#include "../../include/logger/logger_base.h"
#include "../../include/vision/vision.h"

#define START_SIGNAL "START"
#define STOP_SIGNAL "STOP"

void print_vision_data(void) {
    const SensorState *sensors = get_sensors();
    const uint8_t extra_sensors_byte =
        (sensors->left_sensor << 0) | (sensors->central_sensor << 1) |
        (sensors->middle_sensor << 2) | (sensors->right_sensor << 3);

    // Use HAL functions directly to reduce overhead in the main loop
    usart_transmit(sensors->central_sensors_state);
    usart_transmit(extra_sensors_byte);
}

void send_start_signal(void) { print(START_SIGNAL); }

void send_stop_signal(void) { print(STOP_SIGNAL); }
