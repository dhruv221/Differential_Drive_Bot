#include "encoders.h"
#include "motors.h"
#include "motion_profile.h"
#include "pd_controller.h"

float prevX, prevA;

void setup() {
  Serial.begin(115200);
  setup_motors();
  set_left_motor_pwm(153);
  set_right_motor_pwm(153);
  delay(4000);
}

void loop() {
  float X = robot_position();
  float A = robot_angle();
  float speed = X - prevX;
  float omega = A - prevA;
  prevX = X;
  prevA = A;
  Serial.print(speed);
  Serial.print(", ");
  Serial.print(omega);
  Serial.println();
  delay(1000);
}


//---------------------------------------//
//----core1_dist_&_angle_compute_isrs----//
void setup1() {
  setup_encoders();
}

void loop1() {
  update_encoders();
}
