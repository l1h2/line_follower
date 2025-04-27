#include "../../include/receiver/serial.h"

#include "../../include/pid/pid.h"
#include "../../include/state_machine/handlers/config_handler.h"

static void handle_command(const Command command) {
    switch (command.command) {
        case START:
            set_can_run(true);
            break;
        case STOP:
            set_can_run(false);
            break;
        case SET_KP:
            set_kp(command.value);
            break;
        case SET_KI:
            set_ki(command.value);
            break;
        case SET_KD:
            set_kd(command.value);
            break;
        case SET_BASE_PWM:
            set_base_pwm(command.value);
            break;
        case SET_MAX_PWM:
            set_max_pwm(command.value);
            break;
        case SET_RUNNING_MODE:
            set_running_mode((RunningModes)command.value);
            break;
        case SET_STOP_MODE:
            set_stop_mode((StopModes)command.value);
            break;
        case SET_LAPS:
            set_laps(command.value);
            break;
        case SET_STOP_TIME:
            set_stop_time(command.value);
            break;
        default:
            return;
    }
}

bool process_serial_commands(void) {
    Command command = read_command();

    if (command.command == INVALID_COMMAND) return false;

    handle_command(command);
    return true;
}
