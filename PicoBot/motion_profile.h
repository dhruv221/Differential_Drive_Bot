/*
* File: motion_profile.h
* Author: Dhruv Wadhwa
* Created: 28-07-2023 3:33PM
* Last Modified: 28-08-2023 9:36PM
* Description:
* generate smooth position and angle values
* using current position, speed, angle.
* also apply pd corrections
*
* Copyright (c) 2023 Dhruv Wadhwa
*/

#ifndef MOTION_PROFILE_H
#define MOTION_PROFILE_H

class motion_profile {

private:
  //states:
  uint8_t STATE = 0;
  uint8_t IDLE = 0;
  uint8_t ACCELERATING = 1;
  uint8_t BRAKING = 2;
  uint8_t FINISHED = 3;
  //functionality
  int8_t sign = 1;         //+ve or -ve speed
  float SAMPLE_TIME;       //sample time
  float robot_distance;    //current pos
  float robot_speed;       //current speed
  float final_distance;    //final dist
  float final_angle;       //final angle
  int16_t target_speed;    //target speed
  int16_t final_speed;     //final speed
  int16_t acceleration;    //acceleration
  float acceleration_inv;  //precomputed 1/acc
  float setpoint;          //output fwd setpoints


public:

  void reset() {
    robot_distance = 0;
    robot_speed = 0;
    final_distance = 0;
    final_angle = 0;
    target_speed = 0;
    final_speed = 0;
    acceleration = 0;
    setpoint = 0;
  }

  void set_sample_time(float sampleTime) {
    SAMPLE_TIME = sampleTime;
  }

  uint8_t is_finished() {
    return STATE == FINISHED;
  }

  float get_braking_dist() {
    return fabs(final_speed * final_speed - robot_speed * robot_speed) * 0.5 * acceleration_inv;
  }

  void stop() {
    target_speed = 0;
  }

  void start(float dist, float topSpeed, float finalSpeed, float acc) {
    sign = (dist < 0) ? -1 : +1;
    if (dist < 0) {
      dist = fabs(dist);
    }
    if (dist < 1) {
      STATE = FINISHED;
      return;
    }
    if (finalSpeed > topSpeed) {
      finalSpeed = topSpeed;
    }
    robot_distance = 0;
    final_distance = fabs(dist);
    target_speed = sign * fabs(topSpeed);
    final_speed = sign * fabs(finalSpeed);
    acceleration = acc;
    acceleration_inv = 1.0f / acceleration;
    STATE = ACCELERATING;
  }

  void update() {
    if (STATE == IDLE) { return; }
    float deltaspeed = acceleration * SAMPLE_TIME;
    float remaining_dist = fabs(final_distance) - fabs(robot_distance);
    //if braking modify target speed
    if (STATE == ACCELERATING) {
      if (remaining_dist < get_braking_dist()) {
        STATE = BRAKING;
        if (final_speed == 0) { target_speed = sign * 5.0; } 
        else { target_speed = final_speed; }
      }
    }
    //robot increases speed upto target speed
    if (robot_speed < target_speed) {
      robot_speed += deltaspeed;
      if (robot_speed > target_speed) {
        robot_speed = target_speed;
      }
    }
    //robot decreases speed upto target speed
    if (robot_speed > target_speed) {
      robot_speed -= deltaspeed;
      if (robot_speed < target_speed) {
        robot_speed = target_speed;
      }
    }
    //so compute the position output
    robot_distance += robot_speed * SAMPLE_TIME;
    setpoint = robot_distance;
    if (STATE != FINISHED && remaining_dist < 0.2) {
      STATE = FINISHED;
      target_speed = final_speed;
    }
  }

  float get_setpoint() {
    return setpoint;
  }

  float get_speed() {
    return robot_speed;
  }

//class end
};

#endif

//----usage----//
// motion_profile a;
// a.reset();
// a.set_sample_time(0.002);
// a.start(300, 200, 0, 2000);
// a.update();
// a.get_setpoint()
