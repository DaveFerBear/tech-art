# define LED_PIN 13

#include "motorWrapper.cpp"

void setup()
{
  Serial.begin(9600);

  // Sensors
  pinMode(LED_PIN, OUTPUT);

  // Relays
  pinMode(m1_r1, OUTPUT);
  pinMode(m1_r2, OUTPUT);
  pinMode(m2_r1, OUTPUT);
  pinMode(m2_r2, OUTPUT);

  // Motors
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  // Limit switches
  pinMode(l1, INPUT);
  pinMode(l2, INPUT);
  pinMode(l3, INPUT);
  pinMode(l4, INPUT);

  // Encoders
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(encoderPinA), ISR_A, CHANGE);
//  attachInterrupt(digitalPinToInterrupt(encoderPinB), ISR_B, CHANGE);

  // Zero all motors.
  set_motor_speed(1, 0);
  set_motor_speed(2, 0);
  //zero_routine();
}

int getIRDistance(int pin) {
  // Mapping function: http://mess.uwaterloo.ca/datasheet/481D.pdf
  int cm = 14.0 / (float(analogRead(pin)) / 1023.0 * 5.0);
  if (cm > 150) cm = 150;

  // Alternate datasheet: http://mess.uwaterloo.ca/datasheet/480D.pdf
  // int cm = 22.33/((float(analogRead(pin))/1023.0*5.0) - 0.189) - 0.42;
  return cm;
}

int in_int, in_motor, in_duration;
void wait_for_serial() {
  set_motor_speed(1, 0);
  set_motor_speed(2, 0);
  while (!Serial.available()) {
    //Do Absolutely Nothing until something is received over the serial port
  }
}
void user_input_mode() {
  Serial.println("Select Motor (1/2): ");
  wait_for_serial();
  in_motor = Serial.parseInt();
  Serial.println("Select Speed (-255, 255): ");
  wait_for_serial();
  in_int = Serial.parseInt();
  Serial.println("Select Duration (ms): ");
  wait_for_serial();
  in_duration = Serial.parseInt();

  set_motor_speed(in_motor, in_int);
  delay(in_duration);
  int brake_limit = 0;
  if (in_int > 0) {
    brake_limit = -1;
  }
  set_motor_speed(in_motor, brake_limit);
  delay(100);
  set_motor_speed(in_motor, 0);
  delay(1000);
}
void loop()
{
  user_input_mode();
}

