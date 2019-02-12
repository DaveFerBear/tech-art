#define NUM_IR 4

//#include "sensorWrapper.cpp"

int IR_sensors[NUM_IR] = {A8, A9, A10, A11};
//SensorWrapper sw;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_IR; i++)
    pinMode(IR_sensors[i], INPUT);
}

void loop() {
  for (int i = 0; i < NUM_IR; i++) {
    Serial.print(getIRDistance(IR_sensors[i]));
    Serial.print("\t");
  }
  
  Serial.println();
  delay(10);
}

int read_pin_robust(int pin) {
  int num_readings = 20;
  int sum = 0;
  for (int i = 0; i < num_readings; i++) {
    sum += analogRead(pin);
  }
  return sum/num_readings;
}
