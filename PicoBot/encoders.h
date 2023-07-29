/*
* File: encoders.h
* Author: Dhruv Wadhwa
* Created: 28-07-2023 2:53AM
* Last Modified: 29-07-2023 6:56PM
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

static volatile unsigned int left_encoder_copy;    //holds encoder_left_counter
static volatile unsigned int right_encoder_copy;   //holds encoder_left_counter
static volatile unsigned int left_encoder_total;   //total pulses left
static volatile unsigned int right_encoder_total;  //total pulses right
static float robot_ds = 0;                         //ds
static float robot_dtheta = 0;                     //dtheta
static volatile float robot_d;                     //d
static volatile float robot_theta;                 //theta



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
  robot_d = 0;
  robot_theta = 0;
  left_encoder_total = 0;
  right_encoder_total = 0;
}

void update_encoders() {

  //get encoder counters safely and reset
  noInterrupts();
  left_encoder_copy = encoder_left_counter;
  right_encoder_copy = encoder_right_counter;
  encoder_left_counter = 0;
  encoder_right_counter = 0;
  interrupts();

  //total left and right pulses
  left_encoder_total += left_encoder_copy;
  right_encoder_total += right_encoder_copy;
  //ds of left and right wheels
  float left_change = left_encoder_copy * MM_PER_COUNT_LEFT;
  float right_change = right_encoder_copy * MM_PER_COUNT_RIGHT;
  //ds, dtheta
  robot_ds = 0.5 * (right_change + left_change);
  robot_dtheta = (right_change - left_change) * DEG_PER_MM_DIFFERENCE;
  //d, theta
  robot_d += robot_ds;
  robot_theta += robot_dtheta;
}

float robot_position() {
  float distance;
  distance = robot_d;
  return distance;
}

float robot_angle() {
  float angle;
  angle = robot_theta;
  return angle;
}

float robot_fwd_increment() {
  float distance;
  distance = robot_ds;
  return distance;
}

float robot_rot_increment() {
  float distance;
  distance = robot_dtheta;
  return distance;
}

unsigned int encoder_left_total() {
  return left_encoder_total;
}

unsigned int encoder_right_total() {
  return right_encoder_total;
}

#endif
