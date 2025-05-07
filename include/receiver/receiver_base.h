#ifndef RECEIVER_BASE_H
#define RECEIVER_BASE_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initializes the receiver module.
 */
void receiver_init(void);

/**
 * @brief Reads the last available transmission in the buffer.
 * @return The last character received.
 */
char read_transmission(void);

/**
 * @brief Reads the transmission buffer.
 * @param buffer_out The output buffer to store the received data.
 * @param size The number of bytes to read.
 * @warning Make sure the buffer is large enough to hold the received data.
 */
void read_buffer(char *buffer_out, const uint8_t size);

/**
 * @brief Checks if data is available for reading.
 * @return True if data is available, false otherwise.
 */
bool read_available(void);

/**
 * @brief Checks if the transmission buffer is full.
 * @return True if the output buffer is full, false otherwise.
 */
bool read_buffer_full(void);

/**
 * @brief Reads a character from the receiver.
 * @return The received character.
 * @note This function will block until a character is received.
 */
char read_char(void);

/**
 * @brief Reads data from the receiver into a buffer.
 * @param buffer_out The output buffer to store the received data.
 * @param chars The number of characters to read.
 * @note This function will block until all characters are received or a newline
 * is encountered.
 * @note The buffer will be null-terminated.
 * @warning Make sure the buffer is large enough to hold the received data.
 */
void read(char *buffer_out, const uint8_t chars);

#endif  // RECEIVER_BASE_H
