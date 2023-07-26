#include "motors.h"








void setup() {
  setup_motors();
  set_left_motor_pwm(-255);
  set_right_motor_pwm(-255);
}

void loop() {
}
