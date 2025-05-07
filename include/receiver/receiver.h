#ifndef RECEIVER_H
#define RECEIVER_H

#include "../config.h"

#if defined(DEBUG_MODE) || defined(BLUETOOTH_MODE)
#include "receiver_base.h"
#else
#define receiver_init() ((void)0)
#define read_transmission() ((char)0)
#define read_buffer(buffer_out, size) ((char *)0)
#define read_available() (false)
#define read_buffer_full() (false)
#define read_char() ((char)0)
#define read(buffer_out, chars) ((char *)0)
#endif  // DEBUG_MODE || BLUETOOTH_MODE

#ifdef BLUETOOTH_MODE
#include "serial.h"
#else
#define read_command() ((Command){INVALID_COMMAND, 0})
#define wait_for_command() ((Command){INVALID_COMMAND, 0})
#define process_serial_commands() ((void)0)
#endif  // BLUETOOTH_MODE

#endif  // RECEIVER_H
