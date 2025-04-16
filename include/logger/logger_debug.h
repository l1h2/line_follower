#ifndef LOGGER_DEBUG_H
#define LOGGER_DEBUG_H

#ifdef DEBUG_MODE
#include "logger.h"
#else
#define logger_init() ((void)0)
#define print_string(str) ((void)0)
#define print(str) ((void)0)
#define print_bit(bit_position, byte) ((void)0)
#define print_byte(byte) ((void)0)
#define print_signed_byte(byte) ((void)0)
#define printWord(word) ((void)0)
#define print_binary(byte) ((void)0)
#define print_sensors() ((void)0)
#define print_errors(errors) ((void)0)
#define print_diagnostics(errors, interval) ((void)0)
#define print_debounce(debounce_timer) ((void)0)
#endif

#endif  // LOGGER_DEBUG_H
