#ifndef LOGGER_VISION_H
#define LOGGER_VISION_H

/**
 * @brief Prints all sensor data optimized for performance.
 */
void print_vision_data(void);

/**
 * @brief Sends a start signal to the logger.
 * @note This signal indicates that all following data sent will be compliant
 * with the vision data format and not valid characters.
 */
void send_start_signal(void);

/**
 * @brief Sends a stop signal to the logger.
 * @note This signal indicates that vision data transmissions have ended and
 * normal logging operations can resume.
 */
void send_stop_signal(void);

#endif  // LOGGER_VISION_H
