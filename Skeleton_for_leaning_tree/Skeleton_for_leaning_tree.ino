// Program takes analog input from infrared sensors and outputs instructions to two motors


#include <math.h>
#include <array_math.h>

// Defines the pins to which the sensors and the motors are connected.
const int s1 = A1;
const int s2 = A2;
const int s3 = A3;
const int m1 = A4;
const int m2 = A5;

// Defines the constant angles at which the sensors are set.
const int a1 = 135;
const int a2 = 90;
const int a3 = 45;

// Defines and initializes the variables to be used in the loop.
double x1 = 0;
double x2 = 0;
double x3 = 0;
double y1 = 0;
double y2 = 0;
double y3 = 0;
double xfinal = 0;
double yfinal = 0;




double x_comp(double mag, double angle) {
  double xval = mag*cos(angle);
  return xval;
}

double y_comp(double mag, double angle) {
  double yval = mag*sin(angle);
  return yval;
}

void setup() {
  // put your setup code here, to run once:

}


void loop() {
  double magnitudes[3] = {analogRead(s1), analogRead(s2), analogRead(s3)};
  double angles[3] = {a1, a2, a3};
  
  //make new x_vals array by mapping x_comp onto magnitudes array and angles array (or make one 2D array with these), do same for y_vals with y_comp  
  x1 = x_comp(mag1, a1);
  x2 = x_comp(mag2, a2);
  x3 = x_comp(mag3, a3);

  y1 = y_comp(mag1, a1);
  y2 = y_comp(mag2, a2);
  y3 = y_comp(mag3, a3);

// map sum onto x_vals and y_vals arrays
  xfinal = x1 + x2 + x3;
  yfinal = y1 + y2 + y3;

  // map xfinal and yfinal onto range of motors (determined by our hardware (slides)

  // send x-instructions to one motor and y-intstructions to the other
  
}
