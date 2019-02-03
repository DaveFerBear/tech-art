int ledPin = 13;
int IRSensorPin = A0;

// Motor, Relay
int m1_r1 = 4;
int m1_r2 = 5;
int m2_r1 = 6;
int m2_r2 = 7;

// Motor Controller
int m1 = 22;
int m2 = 24;

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

void set_motor_direction(int motor, bool dir) {
  if (motor == 1) {
    digitalWrite(m1_r1, dir);
    digitalWrite(m1_r2, dir);
  } else if (motor == 2) {
    digitalWrite(m2_r1, dir);
    digitalWrite(m2_r2, dir);
  }
}

void loop()
{
  set_motor_direction(1, true);
  set_motor_direction(2, true);
  digitalWrite(m1, HIGH);
  digitalWrite(m2, HIGH);
  delay(1000);

  set_motor_direction(1, false);
  set_motor_direction(2, false);
  digitalWrite(m1, HIGH);
  digitalWrite(m2, HIGH);
  delay(1000);
}

