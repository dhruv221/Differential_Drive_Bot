#include "encoders.h"
#include "motors.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print(robot_position());
  Serial.print(", ");
  Serial.print(robot_angle());
  Serial.println();
}


void setup1() {
  setup_encoders();
}

void loop1() {
  update_encoders();
}
