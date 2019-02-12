# define LED_PIN 13

#include "motorWrapper.cpp"

MotorWrapper mw;
void setup()
{
  Serial.begin(9600);
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

