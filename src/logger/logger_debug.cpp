#include "../../include/logger/logger_debug.h"

#include "../../include/pid/errors.h"
#include "../../include/timer/time.h"

static uint16_t last_log_time = 0;

void print_central_sensors(void) {
    const SensorState *sensors = get_sensors();

    for (uint8_t i = 0; i <= 8; i++) {
        if (i < 4) {
            print_bit(i, sensors->central_sensors_state);
        } else if (i == 4) {
            print_bool(sensors->central_sensor);
        } else if (i > 4) {
            print_bit(i - 1, sensors->central_sensors_state);
        }

        if (i != 8) print_string(" - ");
    }
}

void print_sensors(void) {
    const SensorState *sensors = get_sensors();

    print_bool(sensors->left_sensor);
    print_string(" | ");

    print_central_sensors();

    print_string(" | ");
    print_bool(sensors->right_sensor);

    print_string("\r\n");
    print_string("                    ");
    print_bool(sensors->middle_sensor);

    print_string("\r\n");
    print_string("******************************************");
    print_string("\r\n");
    print_string("\r\n");
}

void print_errors(void) {
    const ErrorStruct *errors = get_errors();

    print_string("Error byte: ");
    print_binary(errors->sensors->central_sensors_state);
    print_string(" - Error: ");
    print_signed_byte(errors->error);
    print_string("\r\n");
    print_string("\r\n");
}

void print_diagnostics(const uint16_t interval) {
    if (!time_elapsed(last_log_time, interval)) return;

    last_log_time = time();
    print_errors();
    print_sensors();
}
