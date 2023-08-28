/*
* File: config.h
* Author: Dhruv Wadhwa
* Created: 28-07-2023 2:53AM
* Last Modified: 28-08-2023 9:35PM
* Description:
* contains configuration of hardware (raspberry pi pico or pico w)
* and physical robot parameters
*
* Copyright (c) 2023 Dhruv Wadhwa
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
const float WHEEL_DIAMETER_L = 23.6;  //mm
const float WHEEL_DIAMETER_R = 23.6;  //mm
const float BOT_RADIUS = 39.2;        //mm
const int ENCODER_PULSES = 696;
//----------------------------------//



#endif
