#define NUM_IR 3
#define NUM_US 0

#include <math.h>
#include "Arduino.h" // Used for analogRead()

class SensorWrapper {
  private:
    int IR_sensors[NUM_IR] = {A7, A9, A10};
    double IR_mags[NUM_IR] = {0.0, 0.0, 0.0};
    int IR_angles[NUM_IR] = {-30, 0, 30};
    
    int US_sensors[NUM_US] = {};
    double US_mags[NUM_US] = {};

    double x = 0, y = 0;
    
    double x_comp(double mag, double angle) {
      double xval = mag * cos(angle);
      return xval;
    }

    double y_comp(double mag, double angle) {
      double yval = mag * sin(angle);
      return yval;
    }

  public:
    void test_and_set() {
      for (int i = 0; i < NUM_IR; i++) {
        IR_mags[i] = analogRead(IR_sensors[i]);
      }
      
      // Make new x_vals array by mapping x_comp onto magnitudes array and angles array
      // (or make one 2D array with these), do same for y_vals with y_comp.
      // Finally, map sum onto x_vals and y_vals arrays.
      int xfinal = 0, yfinal=0;
      for (int i = 0; i < NUM_IR; i++) {
        xfinal += x_comp(IR_mags[i], IR_angles[i]);
      }
      for (int i = 0; i < NUM_IR; i++) {
        yfinal += y_comp(IR_mags[i], IR_angles[i]);
      }
    }
    
    double get_x() {
      return this->x;
    }
    
    double get_y() {
      return this->y;
    }
};
