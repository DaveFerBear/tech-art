int ledPin = 13;
int IRSensorPin = A0;

// Motor, Relay
int m1_r1 = 22;
int m1_r2 = 23;
int m2_r1 = 24;
int m2_r2 = 25;

// Motor Controller
int m1 = 6;
int m2 = 7;

void setup()
{
  Serial.begin(9600);

  // Sensors
  pinMode(ledPin, OUTPUT);
  pinMode(IRSensorPin, INPUT);

  // Relays
  pinMode(m1_r1, OUTPUT);
  pinMode(m1_r2, OUTPUT);
  pinMode(m2_r1, OUTPUT);
  pinMode(m2_r2, OUTPUT);

  // Motors
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  // Zero all motors.
  set_motor_speed(1, 100);
  set_motor_speed(2, 100);
}

int getIRDistance(int pin) {
  // Mapping function: http://mess.uwaterloo.ca/datasheet/481D.pdf
  int cm = 14.0 / (float(analogRead(pin))/1023.0*5.0);
  if (cm > 150) cm=150;
  
  // Alternate datasheet: http://mess.uwaterloo.ca/datasheet/480D.pdf
  // int cm = 22.33/((float(analogRead(pin))/1023.0*5.0) - 0.189) - 0.42;
  return cm;
}

void set_motor_direction(int motor, bool forward) {
  if (motor == 1) {
    digitalWrite(m1_r1, forward);
    digitalWrite(m1_r2, forward);
  } else if (motor == 2) {
    digitalWrite(m2_r1, forward);
    digitalWrite(m2_r2, forward);
  }
}

void set_motor_speed(int motor, int speed) {
  // speed within [-255,255]
  int reverse = false;
  if (speed < 0) {
    reverse = true;
  }

  set_motor_direction(motor, !reverse);
  if (motor == 1) {
    analogWrite(m1, abs(speed));
  } else if (motor == 2) {
    analogWrite(m2, abs(speed));
  }
}

void loop()
{
//  int speed = 255;
//  set_motor_speed(1, speed);
//  set_motor_speed(2, speed);
//  delay(3000);
//
//  set_motor_speed(1, 0);
//  set_motor_speed(2, 0);
//  delay(3000);
//  
//  set_motor_speed(1, -1*speed);
//  set_motor_speed(2, -1*speed);
//  delay(3000);

  set_motor_speed(1, -105);
  set_motor_speed(2, -105);
}

