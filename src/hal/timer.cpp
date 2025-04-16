#include "../../include/hal/timer.h"

#include <avr/interrupt.h>
#include <avr/io.h>

// Timer scale for 100ms with prescaler 1024 and OCR2A value of 222
// (Experimental)
#define TIMER_SCALE 7

static volatile uint16_t system_time = 0;      // System time in deciseconds
static volatile uint8_t overflow_counter = 0;  // Overflow counter for Timer2

void timer_init(void) {
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  // Set prescaler to 1024
    OCR2A = 222;  // Set compare value for 100ms counter (Experimental)

    TIMSK2 |= (1 << OCIE2A);  // Enable Timer2 compare interrupt
    sei();                    // Enable global interrupts
}

ISR(TIMER2_COMPA_vect) {
    overflow_counter++;
    if (overflow_counter >= TIMER_SCALE) {  // 0.1 second has passed
        overflow_counter = 0;               // Reset overflow counter
        system_time++;                      // Increment system time every 100ms
    }
}

uint16_t time(void) {
    uint16_t current_time;
    cli();  // Disable interrupts to ensure atomic access
    current_time = system_time;
    sei();  // Re-enable interrupts
    return current_time;
}

bool time_elapsed(const uint16_t last_time, const uint16_t interval) {
    const uint16_t current_time = time();
    return (current_time - last_time) >= interval;
}

void wait(const uint16_t interval) {
    const uint16_t start_time = time();
    while (!time_elapsed(start_time, interval));
}
