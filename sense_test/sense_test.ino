#define NUM_IR 4

#include "sensorWrapper.cpp"

SensorWrapper sw;

void setup() {
  Serial.begin(9600);
  sw.setup();
}

void loop() {
  sw.test_and_set(); // CALL THIS!
//  int* mags = sw.get_IR_mags();
//  
//  for (int i = 0; i < NUM_IR; i++) {
//    Serial.print(mags[i]);
//    Serial.print("\t");
//  }
  double x = sw.get_x();
  double y = sw.get_y();

  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  
  Serial.println();
  delay(10);
}
