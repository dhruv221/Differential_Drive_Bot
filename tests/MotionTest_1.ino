#include "encoders.h"
#include "motors.h"
#include "motion_profile.h"
#include "pd_controller.h"

motion_profile forward;
motion_profile rotation;
long t_prev = 0;
float target_x = 0;
float target_a = 0;
float fwd_speed = 0;
uint8_t base_pwm = 0;
bool step1 = 0;

void setup() {
  Serial.begin(115200);
  setup_motors();
  forward.reset();
  rotation.reset();
  forward.set_sample_time(0.002);
  rotation.set_sample_time(0.002);
  forward.start(300, 300, 300, 1000);
  rotation.start(0, 200, 0, 1000);
  delay(4000);
}

void loop() {
  float X = robot_position();
  float A = robot_angle();
  float l_w = fwd_speed + fwd_controller(X, target_x) - rot_controller(A, target_a) - 20;
  float r_w = fwd_speed + fwd_controller(X, target_x) + rot_controller(A, target_a);
  Serial.print(l_w);
  Serial.print(",  ");
  Serial.println(A);
  set_left_motor_pwm(get_pwm(l_w));
  set_right_motor_pwm(get_pwm(r_w));


  if(forward.is_finished() && step1 == 0) {
    step1 = 1;
    rotation.start(95, 200, 0, 1000);
    // if (rotation.is_finished()) {
    //   forward.start(10, 200, 0, 700);
    // }
  }

  if (millis() - t_prev > 2) {
    t_prev = millis();
    forward.update();
    rotation.update();
    target_x = forward.get_setpoint();
    target_a = rotation.get_setpoint();
    fwd_speed = forward.get_speed();
    base_pwm = get_pwm(fwd_speed);
    //base_pwm = 0;
  }
  //delay(1000);
}



//---------------------------------------//
//----core1_dist_&_angle_compute_isrs----//
void setup1() {
  setup_encoders();
}

void loop1() {
  update_encoders();
}
