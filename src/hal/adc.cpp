#include "../../include/hal/adc.h"

#include <avr/io.h>
#include <stdbool.h>

#include "../../include/hal/sensors.h"

static bool adc_initialized = false;
static uint8_t channel = BATTERY_CELL;

void adc_init(void) {
    if (adc_initialized) return;

    // AVcc with external capacitor at AREF, (8-bit precision)
    ADMUX = (1 << REFS0) | (1 << ADLAR);

    // Enable ADC, prescaler = 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    adc_initialized = true;
}

uint8_t get_adc_channel(void) { return channel; }

void change_adc_channel(uint8_t new_channel) {
    if (new_channel > 7) return;

    channel = new_channel;
}

uint8_t read_adc(void) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));

    return ADCH;
}

void start_auto_trigger(void) {
    if (!adc_initialized) adc_init();

    ADCSRA |= (1 << ADATE);
    ADCSRB = 0x03;  // Timer/Counter0 compare match A trigger

    ADCSRA |= (1 << ADSC);  // Start conversion
}

void stop_auto_trigger(void) {
    ADCSRA &= ~(1 << ADATE);  // Disable auto-triggering
}

uint8_t get_last_adc(void) { return ADCH; }
