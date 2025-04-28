#include "../../include/hal/timer.h"

#include <avr/interrupt.h>
#include <avr/io.h>

static bool timer_initialized = false;
static volatile uint32_t system_time = 0;  // System time in milliseconds

void timer_init(void) {
    if (timer_initialized) return;

    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22);  // Set prescaler to 64
    OCR2A = 248;            // Set compare value for 1ms counter (Experimental)

    TIMSK2 |= (1 << OCIE2A);  // Enable Timer2 compare interrupt
    sei();                    // Enable global interrupts
}

ISR(TIMER2_COMPA_vect) { system_time++; }

uint32_t get_system_time(void) {
    uint32_t current_time;
    cli();  // Disable interrupts to ensure atomic access
    current_time = system_time;
    sei();  // Re-enable interrupts
    return current_time;
}
