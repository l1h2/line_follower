#ifndef USART_H
#define USART_H

#include <stdint.h>

#define F_CPU 16000000UL  // CPU frequency in Hz
#define BAUD 9600         // Baud rate for USART communication

#define TX_BUFFER_SIZE 32  // Size of the USART buffer for transmission
#define RX_BUFFER_SIZE 2   // Size of the USART buffer for reception

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
 * @brief Reads the last character received.
 * @return The last character received.
 */
char usart_read_last_char(void);

/**
 * @brief Reads the buffer and clears it.
 * @param buffer_out The output buffer to store the received data.
 * @return The output buffer with the received data.
 */
char *usart_read_buffer(char *buffer_out);

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
