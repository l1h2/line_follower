#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

// #define DEBUG_MODE      // Comment to disable debug mode
#define BLUETOOTH_MODE  // Comment to disable Bluetooth mode

// Comment to use milliseconds instead of microseconds (Highly imprecise ~100us
// uncertainty)
// #define US_SYSTEM_TIME

#ifdef US_SYSTEM_TIME
#define TIME_MULTIPLIER 1000  // Time multiplier for microseconds
#else
#define TIME_MULTIPLIER 1  // Time multiplier for milliseconds
#endif

#endif  // LINE_FOLLOWER_H
