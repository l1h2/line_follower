#include "../../include/logger/bluetooth_base.h"

#include "../../include/battery/battery.h"
#include "../../include/logger/logger_base.h"

#define SERIAL_BATTERY "BATTERY:"      // Battery value
#define SERIAL_START_SIGNAL "START"    // Start signal for the receiver
#define SERIAL_STOP_SIGNAL "STOP"      // Stop signal for the receiver
#define SERIAL_STATE "STATE:"          // State of the robot
#define SERIAL_RUNNING_MODE "R_MODE:"  // Running mode of the robot
#define SERIAL_STOP_MODE "S_MODE:"     // Stop mode of the
#define SERIAL_LAPS "LAPS:"            // Number of laps to run
#define SERIAL_STOP_TIME "S_TIME:"     // Time in seconds for the robot to stop
#define SERIAL_LOG_DATA "L_DATA:"      // Data to be logged
#define SERIAL_KP "KP:"                // Proportional gain
#define SERIAL_KI "KI:"                // Integral gain
#define SERIAL_KD "KD:"                // Derivative gain
#define SERIAL_BASE_PWM "BASE_PWM:"    // Base PWM value
#define SERIAL_MAX_PWM "MAX_PWM:"      // Maximum PWM value

static void send_data(const char *key, const uint8_t value) {
    print_string(key);
    print_char(value);
    print_new_line();
}

void send_battery_value(void) {
    send_data(SERIAL_BATTERY, get_battery_value());
}

void send_start_signal(void) { print(SERIAL_START_SIGNAL); }
void send_stop_signal(void) { print_string(SERIAL_STOP_SIGNAL); }

void send_state_machine_info(const StateMachine *sm,
                             const SerialSmOutputs info) {
    switch (info) {
        case STATE:
            send_data(SERIAL_STATE, sm->current_state);
            break;
        case RUNNING_MODE:
            send_data(SERIAL_RUNNING_MODE, sm->running_mode);
            break;
        case STOP_MODE:
            send_data(SERIAL_STOP_MODE, sm->stop_mode);
            break;
        case LAPS:
            send_data(SERIAL_LAPS, sm->laps);
            break;
        case STOP_TIME:
            send_data(SERIAL_STOP_TIME, sm->stop_time / 1000);
            break;
        case LOG_DATA:
            send_data(SERIAL_LOG_DATA, sm->log_data);
            break;
    }
}

void send_pid_info(const PidStruct *pid, const SerialPidOutputs info) {
    switch (info) {
        case KP:
            send_data(SERIAL_KP, pid->kp);
            break;
        case KI:
            send_data(SERIAL_KI, pid->ki);
            break;
        case KD:
            send_data(SERIAL_KD, pid->kd == 1000 ? 255 : pid->kd);
            break;
        case BASE_PWM:
            send_data(SERIAL_BASE_PWM, pid->base_pwm);
            break;
        case MAX_PWM:
            send_data(SERIAL_MAX_PWM, pid->max_pwm);
            break;
    }
}
