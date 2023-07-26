#include "encoders.h"


void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print(encoder_left_counter);
  Serial.print(", ");
  Serial.println(encoder_right_counter);
}




void setup1() {
  setup_encoders();
}

void loop1() {

}