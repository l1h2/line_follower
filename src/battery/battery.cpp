#include "../../include/battery/battery.h"

#include "../../include/hal/adc.h"
#include "../../include/hal/sensors.h"

#define BATTERY_CELL_THRESHOLD 180  // Minimum value for batter cell

static bool battery_monitor_enabled = false;

void battery_monitor_init(void) {
    change_adc_channel(BATTERY_CELL);
    adc_init();
}

void enable_battery_monitor(void) {
    if (battery_monitor_enabled) return;

    change_adc_channel(BATTERY_CELL);
    start_auto_trigger();

    battery_monitor_enabled = true;
}

void disable_battery_monitor(void) {
    stop_auto_trigger();
    battery_monitor_enabled = false;
}

static uint8_t read_battery_value(void) {
    const uint8_t current_adc_channel = get_adc_channel();

    change_adc_channel(BATTERY_CELL);
    const uint8_t battery_value = read_adc();
    change_adc_channel(current_adc_channel);

    return battery_value;
}

static uint8_t get_last_battery_update(void) { return get_last_adc(); }

uint8_t get_battery_value(void) {
    return battery_monitor_enabled ? get_last_battery_update()
                                   : read_battery_value();
}

bool is_battery_low(void) {
    return (get_last_battery_update() < BATTERY_CELL_THRESHOLD);
}
