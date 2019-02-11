#define NUM_IR 3
int IR_sensors[NUM_IR] = {A7, A9, A10};

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < NUM_IR; i++)
    pinMode(IR_sensors[i], INPUT);
}

void loop() {
  for (int i = 0; i < NUM_IR; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(analogRead(IR_sensors[i]));
  }
  delay(500);
}
