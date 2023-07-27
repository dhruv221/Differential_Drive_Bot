#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "config.h"
float ds_left_wheel = 0;
float ds_right_wheel = 0;
float ds = 0;
float dtheta = 0;


void update_odometry() {
  //get change in left and right wheel distance
  ds_left_wheel = encoder_left_counter * (wheel_circumference / encoder_counts_per_rev);
  ds_right_wheel = encoder_right_counter * (wheel_circumference / encoder_counts_per_rev);
  //reset counters
  encoder_left_counter = 0;
  encoder_right_counter = 0;
  //x, y, theta calculations
  ds = (ds_left_wheel + ds_right_wheel) / 2;
  dtheta = (ds_right_wheel - ds_left_wheel) / (2 * bot_radius);
  theta += dtheta;
  float dx = ds * cos(theta);
  float dy = ds * sin(theta);
  X += dx;
  Y += dy;
}
#endif