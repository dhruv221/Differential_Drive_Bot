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

#ifndef CONFIG_H
#define CONFIG_H

//---------Hardware config---------//
//MOTORS
const uint8_t MOTOR_L1 = 16;
const uint8_t MOTOR_L2 = 17;
const uint8_t MOTOR_R1 = 27;
const uint8_t MOTOR_R2 = 26;
//ENCODERS
const uint8_t ENCODER_L = 18;
const uint8_t ENCODER_R = 20;

//---------Global variables---------//
int encoder_left_counter;
int encoder_right_counter;

#endif