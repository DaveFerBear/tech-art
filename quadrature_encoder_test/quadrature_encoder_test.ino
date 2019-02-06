int encoderPinA = 18;
int encoderPinB = 19;

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), ISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), ISR_B, CHANGE);
}

void ISR_A() {
  Serial.println("ISRA");
}

void ISR_B() {
  Serial.println("ISRB");
}

void loop() {
  // put your main code here, to run repeatedly:

}
