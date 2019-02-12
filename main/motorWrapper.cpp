#include "Arduino.h"

class MotorWrapper {
  private:
    // Motor, Relay
    int m1_r1 = 27;
    int m1_r2 = 26;
    int m2_r1 = 28;
    int m2_r2 = 29;

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
    void setup() {
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

      // Encoders
      pinMode(encoderPinA, INPUT_PULLUP);
      pinMode(encoderPinB, INPUT_PULLUP);
      //  attachInterrupt(digitalPinToInterrupt(encoderPinA), ISR_A, CHANGE);
      //  attachInterrupt(digitalPinToInterrupt(encoderPinB), ISR_B, CHANGE);

      // Zero all motors.
      set_motor_speed(1, 0);
      set_motor_speed(2, 0);
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

    void ramp_profile(int motor, int velocity, int duration) {
      int num_steps = 6;
      for (int i = 1; i <= num_steps; i++)
        square_profile(motor, i*velocity/num_steps, duration/2/num_steps);
        
      for (int i = num_steps-1; i >= 0; i--)
        square_profile(motor, i*velocity/num_steps, duration/2/num_steps);
    }
    
    void square_profile(int motor, int velocity, int duration) {
      set_motor_speed(motor, velocity);
      delay(duration);
      if (velocity > 0)
        set_motor_speed(motor, 1);
      else
        set_motor_speed(motor, -1);
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



    ////////////////////////////////////////////////////////////
    //               TEST HELPER FUNCTIONS                    //
    ////////////////////////////////////////////////////////////

    void test_relays() {
      Serial.println("TESTING RELAYS");
      int relays[4] = {this->m1_r1, this->m1_r2, this->m2_r1, this->m2_r2};
      for (int i = 0; i < 4; i++) {
        digitalWrite(relays[i], HIGH);
        delay(250);
        digitalWrite(relays[i], LOW);
        delay(250);
      }
    }
    
};

