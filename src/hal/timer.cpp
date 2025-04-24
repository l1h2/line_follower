#include "../../include/hal/timer.h"

#include <avr/interrupt.h>
#include <avr/io.h>

static bool timer_initialized = false;  // Flag to check if timer is initialized
static volatile uint16_t system_time = 0;  // System time in centiseconds

void timer_init(void) {
    if (timer_initialized) return;

    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  // Set prescaler to 1024
    OCR2A = 152;  // Set compare value for 10ms counter (Experimental)

    TIMSK2 |= (1 << OCIE2A);  // Enable Timer2 compare interrupt
    sei();                    // Enable global interrupts
}

ISR(TIMER2_COMPA_vect) { system_time++; }

uint16_t get_system_time(void) {
    uint16_t current_time;
    cli();  // Disable interrupts to ensure atomic access
    current_time = system_time;
    sei();  // Re-enable interrupts
    return current_time;
}
