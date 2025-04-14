#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>

#include "../pid/pid.h"

/**
 * @brief Initializes USART for logging.
 * @note Should be used instead of usart_init() to ensure proper initialization
 * for logging purposes.
 */
void logger_init(void);

/**
 * @brief Prints a string to the USART.
 * @param str The string to print.
 * @warning Ensure that the string is null-terminated to avoid undefined
 * behavior.
 * @note This function will block until the entire string is transmitted.
 */
void print_string(const char *str);

/**
 * @brief Prints a string to the USART.
 * @param str The string to print.
 * @warning Ensure that the string is null-terminated to avoid undefined
 * behavior.
 * @note This function will block until the entire string is transmitted.
 * @note It adds a newline character at the end of the string.
 */
void print(const char *str);

/**
 * @brief Prints a specific bit of a byte to the USART.
 * @param bit_position The position of the bit to print (0-7).
 * @param byte The byte from which to print the bit.
 */
void print_bit(const uint8_t bit_position, const uint8_t byte);

/**
 * @brief Prints a byte in decimal format to the USART.
 * @param byte The byte to print.
 */
void print_byte(const uint8_t byte);

/**
 * @brief Prints a signed byte in decimal format to the USART.
 * @param byte The byte to print.
 */
void print_signed_byte(int8_t byte);

/**
 * @brief Prints a word (16-bit integer) in decimal format to the USART.
 * @param word The word to print.
 */
void printWord(const uint16_t word);

/**
 * @brief Prints a byte in binary format to the USART.
 * @param byte The byte to print.
 */
void print_binary(const uint8_t byte);

/**
 * @brief Prints the current state of the sensors in a human-readable format.
 */
void print_sensors(void);

/**
 * @brief Prints the error values for PID control in a human-readable format.
 * @param errors The error_struct containing the error values.
 */
void print_errors(const error_struct *errors);

/**
 * @brief Prints the diagnostics information, including sensor states and error
 * values.
 * @param errors The error_struct containing the error values.
 * @param interval The time interval in deciseconds for printing diagnostics.
 * (Default: 10)
 */
void print_diagnostics(const error_struct *errors,
                       const uint16_t interval = 10);

#endif  // LOGGER_H
