#include "../../include/vision/vision.h"

#include "../../include/hal/sensors.h"

void sensors_init(void) { sensor_setup(); }

void update_sensors(SensorState *sensors) {
    sensors->central_sensor = !IR6_ON;
    sensors->left_sensor = !IR1_ON;
    sensors->right_sensor = !IR12_ON;
    sensors->middle_sensor = !IR7_ON;
    sensors->central_sensors_state = CENTRAL_SENSOR_BYTE;
}
