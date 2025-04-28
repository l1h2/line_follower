#ifndef LOGGER_DEBUG_H
#define LOGGER_DEBUG_H

#include <stdint.h>

/**
 * @brief Debug wrapper for the print_char function.
 * @param c The character to print.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_char(const char c);

/**
 * @brief Debug wrapper for the print_bit function.
 * @param bit_position The position of the bit to print.
 * @param byte The byte containing the bit to print.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_bit(const uint8_t bit_position, const uint8_t byte);

/**
 * @brief Debug wrapper for the print_byte function.
 * @param byte The byte to print.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_byte(const uint8_t byte);

/**
 * @brief Debug wrapper for the print_signed_byte function.
 * @param byte The signed byte to print.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_signed_byte(int8_t byte);

/**
 * @brief Debug wrapper for the print_word function.
 * @param word The word to print.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_word(const uint16_t word);

/**
 * @brief Debug wrapper for the print_signed_word function.
 * @param word The signed word to print.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_signed_word(int16_t word);

/**
 * @brief Debug wrapper for the print_binary function.
 * @param byte The byte to print in binary format.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_binary(const uint8_t byte);

/**
 * @brief Debug wrapper for the print_bool function.
 * @param value The boolean value to print.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_bool(const bool value);

/**
 * @brief Debug wrapper for the print_string function.
 * @param str The string to print.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_string(const char *str);

/**
 * @brief Debug wrapper for the print_new_line function.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print_new_line(void);

/**
 * @brief Debug wrapper for the print function.
 * @param str The string to print.
 * @note This function can be used to add print statements that won't be
 * compiled without the DEBUG_MODE directive.
 */
void debug_print(const char *str);

/**
 * @brief Prints the current state of the central sensors in a human-readable
 * format.
 */
void print_central_sensors(void);

/**
 * @brief Prints the current state of the sensors in a human-readable format.
 */
void print_sensors(void);

/**
 * @brief Prints the error values for PID control in a human-readable format.
 */
void print_errors(void);

/**
 * @brief Prints the diagnostics information, including sensor states and error
 * values.
 * @param interval The time interval in milliseconds for printing diagnostics.
 * (Default: 1000)
 */
void print_diagnostics(const uint16_t interval = 1000);

#endif  // LOGGER_DEBUG_H
