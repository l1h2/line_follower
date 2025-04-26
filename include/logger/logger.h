#ifndef LOGGER_H
#define LOGGER_H

#include "../config.h"

#if defined(DEBUG_MODE) || defined(BLUETOOTH_MODE)
#include "logger_base.h"
#else
#define logger_init() ((void)0)
#define print_char(c) ((void)0)
#define print_bit(bit_position, byte) ((void)0)
#define print_byte(byte) ((void)0)
#define print_signed_byte(byte) ((void)0)
#define printWord(word) ((void)0)
#define print_signed_word(word) ((void)0)
#define print_bool(value) ((void)0)
#define print_binary(byte) ((void)0)
#define print_string(str) ((void)0)
#define print_new_line() ((void)0)
#define print(str) ((void)0)
#endif  // DEBUG_MODE || BLUETOOTH_MODE

#ifdef DEBUG_MODE
#include "logger_debug.h"
#else
#define debug_print_char(c) ((void)0)
#define debug_print_bit(bit_position, byte) ((void)0)
#define debug_print_byte(byte) ((void)0)
#define debug_print_signed_byte(byte) ((void)0)
#define debug_print_word(word) ((void)0)
#define debug_print_signed_word(word) ((void)0)
#define debug_print_binary(byte) ((void)0)
#define debug_print_bool(value) ((void)0)
#define debug_print_string(str) ((void)0)
#define debug_print_new_line() ((void)0)
#define debug_print(str) ((void)0)
#define print_central_sensors() ((void)0)
#define print_sensors() ((void)0)
#define print_errors(errors) ((void)0)
#define print_diagnostics(...) ((void)0)
#endif  // DEBUG_MODE

#ifdef BLUETOOTH_MODE
#include "bluetooth_base.h"
#include "bluetooth_logger.h"
#else
#define send_start_signal() ((void)0)
#define send_stop_signal() ((void)0)
#define send_state_info(state) ((void)0)
#define send_mode_info(mode) ((void)0)
#define sen_pid_info(info, value) ((void)0)
#define send_vision_data() ((void)0)
#define send_pid_data() ((void)0)
#define send_data(sm) ((void)0)
#endif  // BLUETOOTH_MODE

#endif  // LOGGER_H
