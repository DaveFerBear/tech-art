#include "Arduino.h"

class MotorWrapper {
  private:
    // Motor, Relay
    int m1_r1 = 22;
    int m1_r2 = 23;
    int m2_r1 = 24;
    int m2_r2 = 25;
    
    // Motor Controller
    int m1 = 6;
    int m2 =  7;
    int m1_speed = 0;
    int m2_speed = 0;
    
    // Limit Switches
    int l1 = 44;
    int l2 = 45;
    int l3 = 46;
    int l4 = 47;
    
    // Encoders
    int encoderPinA = 18;
    int encoderPinB = 19;
    volatile unsigned int encoderPos = 0;
    
  public:
    void MotorWrapper() {
    
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
        m1_speed = speed;
        analogWrite(m1, abs(speed));
      } else if (motor == 2) {
        m2_speed = speed;
        analogWrite(m2, abs(speed));
      }
    }
    
    void cycle_motors_once() {
      int speed = 200;
      set_motor_speed(1, speed);
      set_motor_speed(2, speed);
      delay(2000);
    
      set_motor_speed(1, 1);
      set_motor_speed(2, 1);
      delay(2000);
    
      set_motor_speed(1, -1 * speed);
      set_motor_speed(2, -1 * speed);
      delay(2000);
    
      set_motor_speed(1, -1);
      set_motor_speed(2, -1);
      delay(2000);
    }
    
    void shutdown() {
      Serial.println("Shutting Down.");
      set_motor_speed(1, 0);
      set_motor_speed(2, 0);
      while (1);
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
  set_motor_speed(1, -120);
  while (read_limit_switch_robust(l3) == HIGH);
  set_motor_speed(1, 1);
  set_motor_speed(1, 0);

  delay(2000);

  set_motor_speed(2, -120);
  while (read_limit_switch_robust(l2) == HIGH);
  set_motor_speed(1, 1);
  set_motor_speed(2, 0);

  delay(2000);

  set_motor_speed(1, 120);
  while (read_limit_switch_robust(l4) == HIGH);
  set_motor_speed(1, -1);
  set_motor_speed(1, 0);

  delay(2000);

  set_motor_speed(2, 120);
  while (read_limit_switch_robust(l1) == HIGH);
  set_motor_speed(1, -1);
  set_motor_speed(2, 0);

  delay(2000);
}
};


//void ISR_A() {
//  // look for a low-to-high on channel A
//  if (digitalRead(encoderPinA) == HIGH) {
//
//    // check channel B to see which way encoder is turning
//    if (digitalRead(encoderPinB) == LOW) {
//      Serial.println("HIGH-LOW");
//      encoderPos = encoderPos + 1;         // CW
//    }
//    else {
//      Serial.println("HIGH-HIGH");
//      encoderPos = encoderPos - 1;         // CCW
//    }
//  }
//
//  else   // must be a high-to-low edge on channel A
//  {
//    // check channel B to see which way encoder is turning
//    if (digitalRead(encoderPinB) == HIGH) {
//      Serial.println("LOW-HIGH");
//      encoderPos = encoderPos + 1;          // CW
//    }
//    else {
//      Serial.println("LOW-LOW");
//      encoderPos = encoderPos - 1;          // CCW
//    }
//  }
//  //Serial.println(encoderPos, DEC);
//  // use for debugging - remember to comment out
//
//}
//
//void ISR_B() {
//  // look for a low-to-high on channel B
//  if (digitalRead(encoderPinB) == HIGH) {
//
//    // check channel A to see which way encoder is turning
//    if (digitalRead(encoderPinA) == HIGH) {
//      Serial.println("HIGH-HIGH");
//      encoderPos = encoderPos + 1;         // CW
//    }
//    else {
//      Serial.println("LOW-HIGH");
//      encoderPos = encoderPos - 1;         // CCW
//    }
//  }
//
//  // Look for a high-to-low on channel B
//
//  else {
//    // check channel B to see which way encoder is turning
//    if (digitalRead(encoderPinA) == LOW) {
//      Serial.println("LOW-LOW");
//      encoderPos = encoderPos + 1;          // CW
//    }
//    else {
//      Serial.println("HIGH-LOW");
//      encoderPos = encoderPos - 1;          // CCW
//    }
//  }
//  //Serial.println(encoderPos, DEC);
//}
