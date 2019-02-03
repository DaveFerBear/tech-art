int ledPin = 13;
int motorPin = 12;
int IRSensorPin = A0;

int cnt;

void setup()
{
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(IRSensorPin, INPUT);
  
  cnt = 0;
}

void rampMotor() {
  delay(50);
  cnt += 1;
  cnt = cnt%255;
  analogWrite(ledPin, cnt);
  analogWrite(motorPin, cnt);
}

int getIRDistance(int pin) {
  // Mapping function: http://mess.uwaterloo.ca/datasheet/481D.pdf
  int cm = 12.0 / (float(analogRead(pin)) / 1023.0 * 5.0);
  if (cm > 150) cm=150;
  return cm;
}

void loop()
{
  Serial.println(getIRDistance(IRSensorPin));
}
