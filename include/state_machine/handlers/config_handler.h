#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <stdbool.h>
#include <stdint.h>

#include "../state_machine_base.h"

/**
 * @brief Resets the state machine to its initial state.
 */
void reset_state_machine(void);

/**
 * @brief Restarts the state machine, allowing it to run again.
 */
void restart_state_machine(void);

/**
 * @brief Gets the current state machine instance.
 * @return Pointer to the current state machine instance.
 */
StateMachine* get_state_machine(void);

/**
 * @brief Sets the running mode of the state machine.
 * @param mode The running mode to set.
 */
void set_running_mode(const RunningModes mode);

/**
 * @brief Sets the stopping mode of the state machine.
 * @param mode The stopping mode to set.
 */
void set_stop_mode(const StopModes mode);

/**
 * @brief Sets the can_run flag for the state machine.
 * @param can_run The value to set for the can_run flag.
 */
void set_can_run(const bool can_run);

/**
 * @brief Sets the number of laps for the state machine.
 * @param laps The number of laps to set.
 */
void set_laps(const uint8_t laps);

/**
 * @brief Starts the time for the state machine operation.
 * @param start_time The start time to set.
 */
void set_start_time(void);

/**
 * @brief Sets the stop time for the state machine.
 * @param stop_time The stop time to set.
 */
void set_stop_time(const uint8_t stop_time);

#endif  // CONFIG_HANDLER_H
