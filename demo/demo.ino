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

// Limit Switches
int l1 = 44;
int l2 = 45;
int l3 = 46;
int l4 = 47;

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

  // Limit switches
  pinMode(l1, INPUT);
  pinMode(l2, INPUT);
  pinMode(l3, INPUT);
  pinMode(l4, INPUT);
  
  // Zero all motors.
  set_motor_speed(1, 0);
  set_motor_speed(2, 0);

  zero_routine();
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

void cycle_motors_once() {
  int speed = 200;
  set_motor_speed(1, speed);
  set_motor_speed(2, speed);
  delay(5000);

  set_motor_speed(1, 1);
  set_motor_speed(2, 1);
  delay(5000);
  
  set_motor_speed(1, -1*speed);
  set_motor_speed(2, -1*speed);
  delay(5000);

  set_motor_speed(1, -1);
  set_motor_speed(2, -1);
  delay(5000);  
}

void shutdown() {
  Serial.println("Shutting Down.");
  set_motor_speed(1, 0);
  set_motor_speed(2, 0);
  while(1);
}


// This function assumes pull-up switches.
int read_limit_switch_robust(int swtch) {
  int NUM_READS = 10;
  for (int i = 0; i < NUM_READS; i++) {
    if (digitalRead(swtch) == HIGH)  return HIGH;
  }
  return LOW;
  
}

void zero_routine() {
  set_motor_speed(1, -200);
  while (read_limit_switch_robust(l3) == HIGH);
  set_motor_speed(1, -1);
  set_motor_speed(1, 0);

  delay(2000);

  set_motor_speed(2, -200);
  while (read_limit_switch_robust(l2) == HIGH);
  set_motor_speed(2, 0);

  delay(2000);
}

int in_int, in_motor;
void wait_for_serial() {
  while (!Serial.available()){
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
  
  set_motor_speed(in_motor, in_int);
  delay(250);
  int brake_limit = 0;
  if (in_int > 0) {
    brake_limit = -1;
  }
  set_motor_speed(in_motor, brake_limit);
  delay(100);
  set_motor_speed(in_motor, 0);
}
void loop()
{
  user_input_mode();
}

