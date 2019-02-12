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

  mw.ramp_profile(in_motor, in_int, in_duration);
}

void loop()
{
  
}

