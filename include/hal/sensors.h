#ifndef SENSORS_H
#define SENSORS_H

#include <avr/io.h>

#define IR1 PD2   // Left lateral IR sensor
#define IR2 PD3   // First central IR sensor
#define IR3 PD4   // Second central IR sensor
#define IR4 PC5   // Third central IR sensor
#define IR5 PC4   // Fourth central IR sensor
#define IR6 PC3   // Central IR sensor
#define IR7 PC0   // Middle down IR sensor
#define IR8 PC2   // Fifth central IR sensor
#define IR9 PC1   // Sixth central IR sensor
#define IR10 PD5  // Seventh central IR sensor
#define IR11 PD6  // Eighth central IR sensor
#define IR12 PD7  // Right lateral IR sensor

#define TOTAL_SENSORS 12         // Total number of sensors
#define TOTAL_CENTRAL_SENSORS 8  // Total number of central sensors

#define PIN_IR1 PIND   // Pin for IR1
#define PIN_IR2 PIND   // Pin for IR2
#define PIN_IR3 PIND   // Pin for IR3
#define PIN_IR4 PINC   // Pin for IR4
#define PIN_IR5 PINC   // Pin for IR5
#define PIN_IR6 PINC   // Pin for IR6
#define PIN_IR7 PINC   // Pin for IR7
#define PIN_IR8 PINC   // Pin for IR8
#define PIN_IR9 PINC   // Pin for IR9
#define PIN_IR10 PIND  // Pin for IR10
#define PIN_IR11 PIND  // Pin for IR11
#define PIN_IR12 PIND  // Pin for IR12

#define IR1_MASK (1 << IR1)    // Bit mask for IR1
#define IR2_MASK (1 << IR2)    // Bit mask for IR2
#define IR3_MASK (1 << IR3)    // Bit mask for IR3
#define IR4_MASK (1 << IR4)    // Bit mask for IR4
#define IR5_MASK (1 << IR5)    // Bit mask for IR5
#define IR6_MASK (1 << IR6)    // Bit mask for IR6
#define IR7_MASK (1 << IR7)    // Bit mask for IR7
#define IR8_MASK (1 << IR8)    // Bit mask for IR8
#define IR9_MASK (1 << IR9)    // Bit mask for IR9
#define IR10_MASK (1 << IR10)  // Bit mask for IR10
#define IR11_MASK (1 << IR11)  // Bit mask for IR11
#define IR12_MASK (1 << IR12)  // Bit mask for IR12

#define IR1_ON (PIN_IR1 & IR1_MASK)     // Check if IR1 is on
#define IR2_ON (PIN_IR2 & IR2_MASK)     // Check if IR2 is on
#define IR3_ON (PIN_IR3 & IR3_MASK)     // Check if IR3 is on
#define IR4_ON (PIN_IR4 & IR4_MASK)     // Check if IR4 is on
#define IR5_ON (PIN_IR5 & IR5_MASK)     // Check if IR5 is on
#define IR6_ON (PIN_IR6 & IR6_MASK)     // Check if IR6 is on
#define IR7_ON (PIN_IR7 & IR7_MASK)     // Check if IR7 is on
#define IR8_ON (PIN_IR8 & IR8_MASK)     // Check if IR8 is on
#define IR9_ON (PIN_IR9 & IR9_MASK)     // Check if IR9 is on
#define IR10_ON (PIN_IR10 & IR10_MASK)  // Check if IR10 is on
#define IR11_ON (PIN_IR11 & IR11_MASK)  // Check if IR11 is on
#define IR12_ON (PIN_IR12 & IR12_MASK)  // Check if IR12 is on

// Bit masks for the IR sensors on PORTC
#define PORTC_SENSORS \
    (IR4_MASK | IR5_MASK | IR6_MASK | IR7_MASK | IR8_MASK | IR9_MASK)

// Bit masks for the IR sensors on PORTD
#define PORTD_SENSORS \
    (IR1_MASK | IR2_MASK | IR3_MASK | IR10_MASK | IR11_MASK | IR12_MASK)

#define E1 (IR2_ON >> 3)   // First central IR sensor bit
#define E2 (IR3_ON >> 3)   // Second central IR sensor bit
#define E3 (IR4_ON >> 3)   // Third central IR sensor bit
#define E4 (IR5_ON >> 1)   // Fourth central IR sensor bit
#define E5 (IR8_ON << 2)   // Fifth central IR sensor bit
#define E6 (IR9_ON << 4)   // Sixth central IR sensor bit
#define E7 (IR10_ON << 1)  // Seventh central IR sensor bit
#define E8 (IR11_ON << 1)  // Eighth central IR sensor bit

// Byte organization for central sensors
#define CENTRAL_SENSOR_BYTE ~(E1 | E2 | E3 | E4 | E5 | E6 | E7 | E8)

/**
 * @brief Initializes all IR sensors and enables pull-up resistors.
 */
void sensor_setup(void);

#endif  // SENSORS_H
