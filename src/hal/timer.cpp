#include "../../include/hal/timer.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include "../../include/config.h"

static bool timer_initialized = false;
static bool debug_timer_initialized = false;
static volatile uint32_t system_time = 0;

#ifdef US_SYSTEM_TIME
void timer_init(void) {
    if (timer_initialized) return;

    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS21);  // Set prescaler to 8
    OCR2A = 199;  // Set compare value for 100us counter (Experimental)

    TIMSK2 |= (1 << OCIE2A);  // Enable Timer2 compare interrupt
    sei();                    // Enable global interrupts

    timer_initialized = true;
}
#else
void timer_init(void) {
    if (timer_initialized) return;

    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22);  // Set prescaler to 64
    OCR2A = 249;            // Set compare value for 1ms counter (Experimental)

    TIMSK2 |= (1 << OCIE2A);  // Enable Timer2 compare interrupt
    sei();                    // Enable global interrupts

    timer_initialized = true;
}
#endif

void debug_timer_init(void) {
    if (debug_timer_initialized) return;

    TCCR0A = 0;            // Set Timer0 to normal mode
    TCCR0B = (1 << CS00);  // Set prescaler to 1 (no prescaling)

    debug_timer_initialized = true;
}

void debug_timer_stop(void) {
    TCCR0B = 0;  // Stop Timer0
    debug_timer_initialized = false;
}

#ifdef US_SYSTEM_TIME
// Increment system time by 100us
ISR(TIMER2_COMPA_vect) { system_time += 100; }
#else
ISR(TIMER2_COMPA_vect) { system_time++; }
#endif

uint32_t get_system_time(void) {
    uint32_t current_time;
    cli();  // Disable interrupts to ensure atomic access
    current_time = system_time;
    sei();  // Re-enable interrupts
    return current_time;
}
