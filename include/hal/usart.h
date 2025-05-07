#ifndef USART_H
#define USART_H

#include <stdint.h>

#define F_CPU 16000000UL  // CPU frequency in Hz
#define BAUD 74880        // Baud rate for USART communication

#define TX_BUFFER_SIZE 32  // Size of the USART buffer for transmission
#define RX_BUFFER_SIZE 32  // Size of the USART buffer for reception

/**
 * @brief Initializes the USART transmitter.
 */
void usart_init_transmitter(void);

/**
 * @brief Initializes the USART receiver.
 */
void usart_init_receiver(void);

/**
 * @brief Transmits a byte of data over USART.
 * @param data The byte to transmit.
 */
void usart_transmit(const uint8_t data);

/**
 * @brief Reads one character from the USART buffer.
 * @return char The received character. If no data is available, returns 0.
 */
char usart_read_char(void);

/**
 * @brief Reads from the USART buffer into a provided buffer.
 * @param buffer_out The output buffer to store the received data.
 * @param size The number of bytes to read. If 0, reads all available data.
 * (default: 0)
 * @warning Make sure the buffer is large enough to hold the received data.
 */
void usart_read_buffer(char *buffer_out, uint8_t size = 0);

/**
 * @brief Checks if data is available in the USART buffer.
 * @return The number of bytes available in the buffer to be read.
 */
uint8_t usart_data_available(void);

/**
 * @brief Checks if data has been received.
 * @return True if data has been received, false otherwise.
 */
bool usart_is_data_received(void);

/**
 * @brief Checks if the USART buffer is full.
 * @return True if the buffer is full, false otherwise.
 */
bool usart_is_buffer_full(void);

#endif  // USART_H
