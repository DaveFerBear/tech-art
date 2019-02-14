#define NUM_IR 4

#include <math.h>
#include "Arduino.h" // Used for analogRead()

class SensorWrapper {
  private:
    int IR_sensors[NUM_IR] = {A8, A9, A10, A11};
    int IR_mags[NUM_IR] = {0, 0, 0, 0};
    int IR_angles[NUM_IR] = {-45, -15, 15, 45};

    double x = 0, y = 0;

    double x_comp(double mag, double angle) {
      double xval = mag * cos(angle);
      return xval;
    }

    double y_comp(double mag, double angle) {
      double yval = mag * sin(angle);
      return yval;
    }

    int read_pin_robust(int pin) {
      int num_readings = 20;
      int sum = 0;
      for (int i = 0; i < num_readings; i++) {
        sum += analogRead(pin);
      }
      return sum/num_readings;
    }
    
    int getIRDistance(int pin) {
      int cm = 150;

      if (pin != A10) {
        // Mapping function: http://mess.uwaterloo.ca/datasheet/481D.pdf
        cm = 14.0 / (float(read_pin_robust(pin)) / 1023.0 * 5.0) * 4;
        if (cm > 150) cm = 150;
      } else {

        // Alternate datasheet: http://mess.uwaterloo.ca/datasheet/480D.pdf
        cm = 22.33 / ((float(read_pin_robust(pin)) / 1023.0 * 5.0) - 0.189);
        if (cm > 80) cm = 80;
        cm*=2;
      }
      return cm;
    }

  public:
    void setup() {
      for (int i = 0; i < NUM_IR; i++)
        pinMode(IR_sensors[i], INPUT);
    }
    
    void test_and_set() {
      for (int i = 0; i < NUM_IR; i++) {
        IR_mags[i] = getIRDistance(IR_sensors[i]);
      }

      // Make new x_vals array by mapping x_comp onto magnitudes array and angles array
      // (or make one 2D array with these), do same for y_vals with y_comp.
      // Finally, map sum onto x_vals and y_vals arrays.
      int xfinal = 0, yfinal = 0;
      for (int i = 0; i < NUM_IR; i++) {
        xfinal += x_comp(IR_mags[i], IR_angles[i]);
      }
      for (int i = 0; i < NUM_IR; i++) {
        yfinal += y_comp(IR_mags[i], IR_angles[i]);
      }
      this->x = xfinal;
      this->y = yfinal;
    }

    double get_x() {
      return this->x;
    }

    double get_y() {
      return this->y;
    }

    int* get_IR_mags() {
      return this->IR_mags;
    }
};
