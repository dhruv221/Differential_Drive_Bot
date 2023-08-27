#ifndef CONTROLLER_H
#define CONTROLLER_H

const float fwdKp = 0.15;
const float fwdKd = 1.2;
const float rotKp = 4;
const float rotKd = 2.5;

float fwd_error_curr;
float fwd_error_prev;
float rot_error_curr;
float rot_error_prev;

float right_wheel;
float left_wheel;

uint8_t get_pwm(float speed) {
  uint8_t pwm = (0.21 * speed) + 30;
  if (speed == 0) {
    pwm = 0;
  } 
  else if (pwm > 255) {
    pwm = 255;
  }
  return pwm;
}

float fwd_controller(float x_mes, float x_tgt) {
  fwd_error_curr = x_tgt - x_mes;
  float diff = fwd_error_curr - fwd_error_prev;
  fwd_error_prev = fwd_error_curr;
  float output = fwdKp * fwd_error_curr + fwdKd * diff;
  return output;
}

float rot_controller(float theta_mes, float theta_tgt) {
  rot_error_curr = theta_tgt - theta_mes;
  float diff = rot_error_curr - rot_error_prev;
  rot_error_prev = rot_error_curr;
  float output = rotKp * rot_error_curr + rotKd * diff;
  return output;
}



#endif
