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
//----------------------------------//




//----------bot parameters----------//
const float wheel_circumference = 73.827;   //mm
const float wheel_radius = 23.5;                 //mm
const float bot_radius = 42.55;                  //mm
const int encoder_counts_per_rev = 680;
const float distance_per_count = wheel_circumference / encoder_counts_per_rev;
const float w_calc_helper = (wheel_radius / (2 * bot_radius)); //deg per sec
//----------------------------------//



//---------Global variables---------//
//encoder counters
volatile unsigned int encoder_left_counter = 0;
volatile unsigned int encoder_right_counter = 0;
//odometry
float sample_time = 0.002;  //1ms
float X = 0;
float Y = 0;
float theta = 0;
float v, w;
//----------------------------------//

#endif