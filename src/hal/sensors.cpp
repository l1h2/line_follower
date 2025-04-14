#include "../../include/hal/sensors.h"

void sensor_setup(void) {
    // Set all IR sensors as input
    DDRD &= ~(PORTD_SENSORS);
    DDRC &= ~(PORTC_SENSORS);

    // Enable pull-up resistors for all IR sensors
    PORTD |= (PORTD_SENSORS);
    PORTC |= (PORTC_SENSORS);
}
