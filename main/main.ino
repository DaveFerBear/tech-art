# define LED_PIN 13

#include "motorWrapper.cpp"
#include "sensorWrapper.cpp"

MotorWrapper mw;
SensorWrapper sw;

void setup()
{
  Serial.begin(9600);
  mw.setup();
  pinMode(LED_PIN, OUTPUT);
  //mw.zero_routine();
  Serial.println("Booting Up!");
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

  mw.square_profile(in_motor, in_int, in_duration);
}

int * mags;

#define NUM_SENSOR_READS 10000
long avg1, avg2, avg3, avg4;

void loop()
{
  sw.test_and_set();
  mags = sw.get_IR_mags();

  avg1 = 0;
  avg2 = 0;
  avg3 = 0;
  avg4 = 0;

  for (int k = 0; k < NUM_SENSOR_READS; k++) {
    avg1 += mags[0];
    avg2 += mags[1];
    avg3 += mags[2];
    avg4 += mags[3];
  }
  avg1 /= NUM_SENSOR_READS;
  avg2 /= NUM_SENSOR_READS;
  avg3 /= NUM_SENSOR_READS;
  avg4 /= NUM_SENSOR_READS;

  Serial.print(avg1);
  Serial.print("\t");

  Serial.print(avg2);
  Serial.println("\t");

  Serial.print(avg3);
  Serial.print("\t");

  Serial.println(avg4);

  if (avg1 < 80 || avg2 < 80) {
    mw.run_to_limit_safe(1);
  } else if (avg3 < 80 || avg4 < 80) {
    mw.run_to_limit_safe(2);
  }
}

