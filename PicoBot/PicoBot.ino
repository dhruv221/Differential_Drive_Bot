#include "encoders.h"
#include "odometry.h"
#include "motors.h"


void setup() {
  Serial.begin(115200);
  setup_motors();
  set_left_motor_pwm(130);
  set_right_motor_pwm(130);
}

void loop() {
  update_odometry();
  Serial.print(X);
  Serial.print(", ");
  Serial.print(Y);
  Serial.print(", ");
  Serial.print(theta);
  // // Serial.print(", ");
  // Serial.print(v);
  // Serial.print(", ");
  // Serial.print(w);
  // Serial.print(", ");
  Serial.println();
}




void setup1() {
  setup_encoders();
}

void loop1() {
  
}