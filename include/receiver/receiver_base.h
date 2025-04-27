#ifndef RECEIVER_BASE_H
#define RECEIVER_BASE_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initializes the receiver module.
 */
void receiver_init(void);

/**
 * @brief Gets the size of the receiver buffer.
 * @return The size of the receiver buffer.
 */
uint8_t buffer_size(void);

/**
 * @brief Reads the last character received.
 * @return The last character received.
 */
char read_last_transmission(void);

/**
 * @brief Reads the transmission buffer.
 * @param buffer_out The output buffer to store the received data.
 * @return The output buffer with the received data.
 */
char *read_raw_buffer(char *buffer_out);

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
 * @return The output buffer with the received data.
 * @note This function will block until the buffer is full.
 */
char *read(char *buffer_out);

#endif  // RECEIVER_BASE_H
