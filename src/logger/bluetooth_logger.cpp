#include "../../include/logger/bluetooth_logger.h"

#include <stdint.h>

#include "../../include/hal/usart.h"
#include "../../include/logger/bluetooth_base.h"
#include "../../include/pid/pid.h"
#include "../../include/timer/time.h"
#include "../../include/vision/vision.h"

static uint32_t last_log_time = 0;

void send_vision_data(void) {
    const SensorState *sensors = get_sensors();
    const uint8_t extra_sensors_byte =
        (sensors->left_sensor << 0) | (sensors->central_sensor << 1) |
        (sensors->middle_sensor << 2) | (sensors->right_sensor << 3);

    // Use HAL functions directly to reduce overhead in the main loop
    usart_transmit(sensors->central_sensors_state);
    usart_transmit(extra_sensors_byte);
}

void send_pid_data(void) {
    const PidStruct *pid = get_pid();

    send_pid_info(KP, pid->kp);
    send_pid_info(KI, pid->ki);
    send_pid_info(KD, pid->kd);
    send_pid_info(BASE_PWM, pid->base_pwm);
    send_pid_info(MAX_PWM, pid->max_pwm);
}

void send_state_machine_data(const StateMachine *sm) {
    send_state_machine_info(sm, STATE);
    send_state_machine_info(sm, RUNNING_MODE);
    send_state_machine_info(sm, STOP_MODE);
    send_state_machine_info(sm, LAPS);
    send_state_machine_info(sm, STOP_TIME);
    send_state_machine_info(sm, LOG_DATA);
}

void send_robot_data(const StateMachine *sm, const uint32_t interval) {
    if (!time_elapsed(last_log_time, interval)) return;

    last_log_time = time();
    send_battery_value();
    send_state_machine_data(sm);
    send_pid_data();
}
