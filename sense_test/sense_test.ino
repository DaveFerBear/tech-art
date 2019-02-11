#define NUM_IR 3

#include "sensorWrapper.cpp"

int IR_sensors[NUM_IR] = {A8, A9, A10, A11};
SensorWrapper sw;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_IR; i++)
    pinMode(IR_sensors[i], INPUT);
}

void loop() {
  for (int i = 0; i < NUM_IR; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(getIRDistance(IR_sensors[i]));
  }
  
  delay(100);
}

int read_pin_robust(int pin) {
  int num_readings = 20;
  int sum = 0;
  for (int i = 0; i < num_readings; i++) {
    sum += analogRead(pin);
  }
  return sum/num_readings;
}

int getIRDistance(int pin) {
  // Mapping function: http://mess.uwaterloo.ca/datasheet/481D.pdf
  int cm = 14.0 / (float(read_pin_robust(pin)) / 1023.0 * 5.0);
  if (cm > 150) cm = 150;

  // Alternate datasheet: http://mess.uwaterloo.ca/datasheet/480D.pdf
  // int cm = 22.33/((float(analogRead(pin))/1023.0*5.0) - 0.189) - 0.42;
  return cm;
}

