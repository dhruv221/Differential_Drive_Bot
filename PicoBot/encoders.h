/*
 * File: motors.h
 * Project: Micromouse_draft
 * File Created: Thursday, 27th july 2023 12:34 am
 * Author: Dhruv wadhwa
 * -----
 * Last Modified: Thursday, 27th july 2023 12:34 am
 * Modified By: Dhruv wadhwa
 * -----
 * MIT License
 *
 * Copyright (c) 2021 Dhruv Wadhwa
 */
#ifndef ENCODERS_H
#define ENCODERS_H

#include "config.h"

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

#endif