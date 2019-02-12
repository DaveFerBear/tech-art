# define LED_PIN 13

#include "motorWrapper.cpp"

MotorWrapper mw;
void setup()
{
  Serial.begin(9600);
  mw.setup();
  pinMode(LED_PIN, OUTPUT);
  //mw.zero_routine();
}

int in_int, in_motor, in_duration;

void wait_for_serial() {
  mw.set_motor_speed(1, 0);
  mw.set_motor_speed(2, 0);
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

  mw.set_motor_speed(in_motor, in_int);
  delay(in_duration);
  int brake_limit = 0;
  if (in_int > 0) {
    brake_limit = -1;
  }
  mw.set_motor_speed(in_motor, brake_limit);
  delay(100);
  mw.set_motor_speed(in_motor, 0);
  delay(1000);
}

void loop()
{
  //mw.test_relays();
  //user_input_mode();
}

