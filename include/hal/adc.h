#ifndef ADC_H
#define ADC_H

#include <stdint.h>

/**
 * @brief Initialize the ADC (Analog-to-Digital Converter).
 */
void adc_init(void);

/**
 * @brief Get the current ADC channel being read.
 * @return The current ADC channel (0-7).
 */
uint8_t get_adc_channel(void);

/**
 * @brief Change the ADC channel to read from.
 * @param new_channel The new ADC channel (0-7).
 */
void change_adc_channel(uint8_t new_channel);

/**
 * @brief Starts a conversion and returns the ADC value.
 * @return The ADC value.
 */
uint8_t read_adc(void);

/**
 * @brief Starts the ADC auto-triggering.
 */
void start_auto_trigger(void);

/**
 * @brief Stops the ADC auto-triggering.
 */
void stop_auto_trigger(void);

/**
 * @brief Gets the last ADC value read.
 * @return The last ADC value.
 */
uint8_t get_last_adc(void);

#endif  // ADC_H
