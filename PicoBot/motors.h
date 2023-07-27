#ifndef MOTORS_H
#define MOTORS_H

#include "config.h"

void setup_motors() {
  pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_L2, OUTPUT);
  pinMode(MOTOR_R1, OUTPUT);
  pinMode(MOTOR_R2, OUTPUT);
}

void set_left_motor_pwm(int pwm) {
  if (pwm > 0) {
    gpio_set_function(MOTOR_L2, GPIO_FUNC_SIO); //fast digital write
    gpio_put(MOTOR_L2, 0);  
    analogWrite(MOTOR_L1, pwm);
  }
  else {
    gpio_set_function(MOTOR_L1, GPIO_FUNC_SIO); //fast digital write
    gpio_put(MOTOR_L1, 0);
    analogWrite(MOTOR_L2, -1*pwm);
  }
}

void set_right_motor_pwm(int pwm) {
  if (pwm > 0) {
    gpio_set_function(MOTOR_R2, GPIO_FUNC_SIO); //fast digital write
    gpio_put(MOTOR_R2, 0);
    analogWrite(MOTOR_R1, pwm);
  }
  else {
    gpio_set_function(MOTOR_R1, GPIO_FUNC_SIO); //fast digital write
    gpio_put(MOTOR_R1, 0);
    analogWrite(MOTOR_R2, -1*pwm);
  }
}

#endif