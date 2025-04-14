#ifndef USART_H
#define USART_H

#include <stdint.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR (((F_CPU / 16UL) / BAUD) - 1)

/**
 * @brief Sets up the USART registers for communication.
 */
void usart_init(void);

/**
 * @brief Transmits a byte of data over USART.
 * @param data The byte to transmit.
 */
void usart_transmit(const uint8_t data);

/**
 * @brief Receives a byte of data over USART.
 * @return The received byte.
 */
char usart_receive(void);

#endif  // USART_H
