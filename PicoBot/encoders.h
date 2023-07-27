/*
* File: encoders.h
* Author: Dhruv Wadhwa
* Created: 28-07-2023 2:53AM
* Last Modified: 28-07-2023 2:53AM
* Description:
* hardware abstraction N20 encoders
* with position and angle odometry
*
* Copyright (c) 2023 Dhruv Wadhwa
*/

#ifndef ENCODERS_H
#define ENCODERS_H

#include "config.h"

const float MM_PER_COUNT_LEFT = PI * WHEEL_DIAMETER_L / ENCODER_PULSES;
const float MM_PER_COUNT_RIGHT = PI * WHEEL_DIAMETER_R / ENCODER_PULSES;
const float DEG_PER_MM_DIFFERENCE = (180.0 / (2 * BOT_RADIUS * PI));

volatile unsigned int encoder_left_counter;
volatile unsigned int encoder_right_counter;

static volatile unsigned int left_delta;     //holds encoder_left_counter
static volatile unsigned int right_delta;    //holds encoder_left_counter
static volatile unsigned int s_left_total;   //total pulses left
static volatile unsigned int s_right_total;  //total pulses right
static float s_robot_fwd_increment = 0;      //ds
static float s_robot_rot_increment = 0;      //dtheta
static volatile float s_robot_position;      //d
static volatile float s_robot_angle;         //theta



void ENCODER_L_ISR() {
  encoder_left_counter++;
}

void ENCODER_R_ISR() {
  encoder_right_counter++;
}

void setup_encoders() {
  pinMode(ENCODER_L, INPUT_PULLUP);
  pinMode(ENCODER_R, INPUT_PULLUP);
  attachInterrupt(ENCODER_L, ENCODER_L_ISR, FALLING);
  attachInterrupt(ENCODER_R, ENCODER_R_ISR, FALLING);
}

void reset_encoders() {
  noInterrupts();
  encoder_left_counter = 0;
  encoder_right_counter = 0;
  interrupts();
  s_robot_position = 0;
  s_robot_angle = 0;
  s_left_total = 0;
  s_right_total = 0;
  left_delta = 0;
  right_delta = 0;
}

void update_encoders() {

  //get encoder counters safely and reset
  noInterrupts();
  left_delta = encoder_left_counter;
  right_delta = encoder_right_counter;
  encoder_left_counter = 0;
  encoder_right_counter = 0;
  interrupts();

  //total left and right pulses
  s_left_total += left_delta;
  s_right_total += right_delta;
  //ds of left and right wheels
  float left_change = left_delta * MM_PER_COUNT_LEFT;
  float right_change = right_delta * MM_PER_COUNT_RIGHT;
  //ds, dtheta
  s_robot_fwd_increment = 0.5 * (right_change + left_change);
  s_robot_rot_increment = (right_change - left_change) * DEG_PER_MM_DIFFERENCE;
  //d, theta
  s_robot_position += s_robot_fwd_increment;
  s_robot_angle += s_robot_rot_increment;
}

float robot_position() {
  float distance;
  distance = s_robot_position;
  return distance;
}

float robot_angle() {
  float angle;
  angle = s_robot_angle;
  return angle;
}

float robot_fwd_increment() {
  float distance;
  distance = s_robot_fwd_increment;
  return distance;
}

float robot_rot_increment() {
  float distance;
  distance = s_robot_rot_increment;
  return distance;
}

unsigned int encoder_left_total() {
  return s_left_total;
}

unsigned int encoder_right_total() {
  return s_right_total;
}

#endif
