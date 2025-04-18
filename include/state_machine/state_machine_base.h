#ifndef STATE_MACHINE_BASE_H
#define STATE_MACHINE_BASE_H

/**
 * @enum RobotStates
 * @brief Enumeration of robot states for the state machine.
 */
typedef enum {
    STATE_INIT,     // Initial state of the robot
    STATE_IDLE,     // Idle state, waiting for commands
    STATE_RUNNING,  // Running state, executing laps
    STATE_STOPPED,  // Stopped state, waiting for restart
    STATE_ERROR     // Error state, handling errors
} RobotStates;

/**
 * @struct StateMachine
 * @brief Structure representing the state machine.
 */
typedef struct {
    RobotStates previous_state;  // Previous state of the robot
    RobotStates current_state;   // Current state of the robot
    RobotStates next_state;      // Next state of the robot
    uint8_t laps;                // Number of laps to run
} StateMachine;

#endif  // STATE_MACHINE_BASE_H
