int ledPin = 13;
int IRSensorPin = A0;

// Motor, Relay
int m1_r1 = 22;
int m1_r2 = 23;
int m2_r1 = 24;
int m2_r2 = 25;

// Motor Controller
int m1 = A0;
int m2 = A1;

int cnt;

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

  cnt = 0;
}

void rampMotor(int motorPin) {
  delay(50);
  cnt += 1;
  cnt = cnt%255;
  analogWrite(ledPin, cnt);
  analogWrite(motorPin, cnt);
}

int getIRDistance(int pin) {
  // Mapping function: http://mess.uwaterloo.ca/datasheet/481D.pdf
  int cm = 14.0 / (float(analogRead(pin))/1023.0*5.0);
  if (cm > 150) cm=150;
  
  // Alternate datasheet: http://mess.uwaterloo.ca/datasheet/480D.pdf
  // int cm = 22.33/((float(analogRead(pin))/1023.0*5.0) - 0.189) - 0.42;
  return cm;
}

private void set_motor_direction(int motor, bool forward) {
  if (motor == 1) {
    digitalWrite(m1_r1, forward);
    digitalWrite(m1_r2, forward);
  } else if (motor == 2) {
    digitalWrite(m2_r1, forward);
    digitalWrite(m2_r2, forward);
  }
}

private void set_motor_speed(int motor, int speed) {
  // speed within [-255,255]
  int reverse = false;
  if (speed < 0) {
    reverse = true;
  }

  set_motor_direction(motor, reverse);
  if (motor == 1) {
    analogWrite(m1, speed);
  } else if (motor == 2) {
    analogWrite(m2, speed);
  }
}

void cyle_motors() {
  set_motor_direction(1, true);
  set_motor_direction(2, true);
  analogWrite(m1, 1023);
  analogWrite(m2, 1023);
  delay(500);
  analogWrite(m1, 0);
  analogWrite(m2, 0);
  
  delay(2000);

  set_motor_direction(1, false);
  set_motor_direction(2, false);
  analogWrite(m1, 1023);
  analogWrite(m2, 1023);
  delay(500);
  analogWrite(m1, 0);
  analogWrite(m2, 0);

  delay(2000);  
}

void loop()
{
  set_motor_direction(1, true);
  set_motor_direction(2, true);
  
  analogWrite(m1, 1023);
  analogWrite(m2, 1023);
  delay(200);
  
  analogWrite(m1, 0);
  analogWrite(m2, 0);
}

