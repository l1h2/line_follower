#include "../../include/vision/vision.h"

#include "../../include/hal/sensors.h"

static SensorState sensors = {0};

void sensors_init(void) { sensor_setup(); }

void update_sensors() {
    sensors.central_sensor = !IR6_ON;
    sensors.left_sensor = !IR1_ON;
    sensors.right_sensor = !IR12_ON;
    sensors.middle_sensor = !IR7_ON;
    sensors.central_sensors_state = CENTRAL_SENSOR_BYTE;
}

void clear_sensors() {
    sensors.central_sensor = false;
    sensors.left_sensor = false;
    sensors.right_sensor = false;
    sensors.middle_sensor = false;
    sensors.central_sensors_state = 0;
}

const SensorState* get_sensors() { return &sensors; }
