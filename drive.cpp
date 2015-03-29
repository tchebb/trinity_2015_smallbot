/* drive.cpp
 *
 * Drive control code.
 */

#include <Arduino.h>
#include "drive.h"

#include <Servo.h>
#if REFRESH_INTERVAL != 3000
  #error Continuous rotation servos require you to customize the Arduino \
         Servo library. Please change REFRESH_INTERVAL to 3000.
#endif

Calibration::Calibration(int low, int dead_low, int midpoint, int dead_high, int high) {
  this->low = low;
  this->dead_low = dead_low;
  this->midpoint = midpoint;
  this->dead_high = dead_high;
  this->high = high;
}

DriveServo::DriveServo(int pin, const Calibration *c) {
  this->c = c;
  s.attach(pin);

  // Initialize the servo with a signal in the center of its dead zone.
  speed(0);
}

int DriveServo::get_speed() {
  return c_speed;
}

static double mapping[] = {
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  0.6451612903225806,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.2903225806451613,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  1.935483870967742,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  2.5806451612903225,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.225806451612903,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  3.870967741935484,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  4.516129032258064,
  5.161290322580645,
  5.161290322580645,
  5.161290322580645,
  5.161290322580645,
  5.161290322580645,
  5.161290322580645,
  5.161290322580645,
  5.161290322580645,
  5.161290322580645,
  5.161290322580645,
  5.161290322580645,
  5.806451612903226,
  5.806451612903226,
  5.806451612903226,
  5.806451612903226,
  5.806451612903226,
  5.806451612903226,
  5.806451612903226,
  5.806451612903226,
  5.806451612903226,
  5.806451612903226,
  6.451612903225806,
  6.451612903225806,
  6.451612903225806,
  6.451612903225806,
  6.451612903225806,
  6.451612903225806,
  6.451612903225806,
  6.451612903225806,
  6.451612903225806,
  6.451612903225806,
  7.096774193548387,
  7.096774193548387,
  7.096774193548387,
  7.096774193548387,
  7.096774193548387,
  7.096774193548387,
  7.096774193548387,
  7.096774193548387,
  7.096774193548387,
  7.741935483870968,
  7.741935483870968,
  7.741935483870968,
  7.741935483870968,
  7.741935483870968,
  7.741935483870968,
  7.741935483870968,
  7.741935483870968,
  7.741935483870968,
  8.387096774193548,
  8.387096774193548,
  8.387096774193548,
  8.387096774193548,
  8.387096774193548,
  8.387096774193548,
  8.387096774193548,
  8.387096774193548,
  9.032258064516128,
  9.032258064516128,
  9.032258064516128,
  9.032258064516128,
  9.032258064516128,
  9.032258064516128,
  9.032258064516128,
  9.032258064516128,
  9.032258064516128,
  9.67741935483871,
  9.67741935483871,
  9.67741935483871,
  9.67741935483871,
  9.67741935483871,
  9.67741935483871,
  9.67741935483871,
  10.32258064516129,
  10.32258064516129,
  10.32258064516129,
  10.32258064516129,
  10.32258064516129,
  10.32258064516129,
  10.32258064516129,
  10.32258064516129,
  10.96774193548387,
  10.96774193548387,
  10.96774193548387,
  10.96774193548387,
  10.96774193548387,
  10.96774193548387,
  10.96774193548387,
  11.612903225806452,
  11.612903225806452,
  11.612903225806452,
  11.612903225806452,
  11.612903225806452,
  11.612903225806452,
  12.258064516129032,
  12.258064516129032,
  12.258064516129032,
  12.258064516129032,
  12.258064516129032,
  12.258064516129032,
  12.258064516129032,
  12.903225806451612,
  12.903225806451612,
  12.903225806451612,
  12.903225806451612,
  12.903225806451612,
  12.903225806451612,
  13.548387096774194,
  13.548387096774194,
  13.548387096774194,
  13.548387096774194,
  13.548387096774194,
  13.548387096774194,
  13.548387096774194,
  14.193548387096774,
  14.193548387096774,
  14.193548387096774,
  14.193548387096774,
  14.193548387096774,
  14.838709677419354,
  14.838709677419354,
  14.838709677419354,
  14.838709677419354,
  14.838709677419354,
  14.838709677419354,
  15.483870967741936,
  15.483870967741936,
  15.483870967741936,
  15.483870967741936,
  15.483870967741936,
  15.483870967741936,
  16.129032258064516,
  16.129032258064516,
  16.129032258064516,
  16.129032258064516,
  16.129032258064516,
  16.774193548387096,
  16.774193548387096,
  16.774193548387096,
  16.774193548387096,
  16.774193548387096,
  17.419354838709676,
  17.419354838709676,
  17.419354838709676,
  17.419354838709676,
  17.419354838709676,
  17.419354838709676,
  18.064516129032256,
  18.064516129032256,
  18.064516129032256,
  18.064516129032256,
  18.064516129032256,
  18.70967741935484,
  18.70967741935484,
  18.70967741935484,
  18.70967741935484,
  18.70967741935484,
  19.35483870967742,
  19.35483870967742,
  19.35483870967742,
  19.35483870967742,
  20.0,
  20.0,
  20.0,
  20.0,
  20.0,
  20.64516129032258,
  20.64516129032258,
  20.64516129032258,
  20.64516129032258,
  20.64516129032258,
  21.29032258064516,
  21.29032258064516,
  21.29032258064516,
  21.29032258064516,
  21.93548387096774,
  21.93548387096774,
  21.93548387096774,
  21.93548387096774,
  21.93548387096774,
  22.58064516129032,
  22.58064516129032,
  22.58064516129032,
  22.58064516129032,
  23.225806451612904,
  23.225806451612904,
  23.225806451612904,
  23.225806451612904,
  23.225806451612904,
  23.870967741935484,
  23.870967741935484,
  23.870967741935484,
  23.870967741935484,
  24.516129032258064,
  24.516129032258064,
  24.516129032258064,
  24.516129032258064,
  24.516129032258064,
  25.161290322580644,
  25.161290322580644,
  25.161290322580644,
  25.161290322580644,
  25.806451612903224,
  25.806451612903224,
  25.806451612903224,
  25.806451612903224,
  26.451612903225804,
  26.451612903225804,
  26.451612903225804,
  26.451612903225804,
  27.096774193548388,
  27.096774193548388,
  27.096774193548388,
  27.096774193548388,
  27.096774193548388,
  27.741935483870968,
  27.741935483870968,
  27.741935483870968,
  27.741935483870968,
  28.387096774193548,
  28.387096774193548,
  28.387096774193548,
  28.387096774193548,
  29.032258064516128,
  29.032258064516128,
  29.032258064516128,
  29.032258064516128,
  29.677419354838708,
  29.677419354838708,
  29.677419354838708,
  29.677419354838708,
  30.32258064516129,
  30.32258064516129,
  30.32258064516129,
  30.32258064516129,
  30.967741935483872,
  30.967741935483872,
  30.967741935483872,
  30.967741935483872,
  31.612903225806452,
  31.612903225806452,
  31.612903225806452,
  31.612903225806452,
  32.25806451612903,
  32.25806451612903,
  32.25806451612903,
  32.25806451612903,
  32.90322580645161,
  32.90322580645161,
  32.90322580645161,
  32.90322580645161,
  33.54838709677419,
  33.54838709677419,
  33.54838709677419,
  33.54838709677419,
  34.193548387096776,
  34.193548387096776,
  34.193548387096776,
  34.193548387096776,
  34.83870967741935,
  34.83870967741935,
  34.83870967741935,
  34.83870967741935,
  35.483870967741936,
  35.483870967741936,
  35.483870967741936,
  35.483870967741936,
  36.12903225806451,
  36.12903225806451,
  36.12903225806451,
  36.12903225806451,
  36.12903225806451,
  36.774193548387096,
  36.774193548387096,
  36.774193548387096,
  36.774193548387096,
  37.41935483870968,
  37.41935483870968,
  37.41935483870968,
  37.41935483870968,
  38.064516129032256,
  38.064516129032256,
  38.064516129032256,
  38.064516129032256,
  38.70967741935484,
  38.70967741935484,
  38.70967741935484,
  38.70967741935484,
  39.354838709677416,
  39.354838709677416,
  39.354838709677416,
  39.354838709677416,
  40.0,
  40.0,
  40.0,
  40.0,
  40.64516129032258,
  40.64516129032258,
  40.64516129032258,
  40.64516129032258,
  41.29032258064516,
  41.29032258064516,
  41.29032258064516,
  41.29032258064516,
  41.935483870967744,
  41.935483870967744,
  41.935483870967744,
  41.935483870967744,
  42.58064516129032,
  42.58064516129032,
  42.58064516129032,
  42.58064516129032,
  43.225806451612904,
  43.225806451612904,
  43.225806451612904,
  43.87096774193548,
  43.87096774193548,
  43.87096774193548,
  44.516129032258064,
  44.516129032258064,
  44.516129032258064,
  45.16129032258064,
  45.16129032258064,
  45.16129032258064,
  45.806451612903224,
  45.806451612903224,
  46.45161290322581,
  46.45161290322581,
  47.096774193548384,
  47.096774193548384,
  47.74193548387097,
  47.74193548387097,
  48.387096774193544,
  49.03225806451613,
  49.03225806451613,
  49.67741935483871,
  50.32258064516129,
  50.96774193548387,
  50.96774193548387,
  51.61290322580645,
  52.25806451612903,
  52.90322580645161,
  53.54838709677419,
  54.193548387096776,
  54.83870967741935,
  55.483870967741936,
  56.12903225806451,
  56.774193548387096,
  57.41935483870967,
  58.064516129032256,
  59.354838709677416,
  60.0,
  60.64516129032258,
  61.29032258064516,
  62.58064516129032,
  63.225806451612904,
  64.51612903225806,
  65.16129032258064,
  66.45161290322581,
  67.09677419354838,
  68.38709677419355,
  69.03225806451613,
  70.3225806451613,
  70.96774193548387,
  72.25806451612902,
  72.90322580645162,
  74.19354838709677,
  75.48387096774194,
  76.12903225806451,
  77.41935483870968,
  78.70967741935483,
  80.0,
  80.64516129032258,
  81.93548387096774,
  83.2258064516129,
  84.51612903225806,
  85.16129032258064,
  86.45161290322581,
  87.74193548387096,
  89.03225806451613,
  90.32258064516128,
  91.61290322580645,
  92.25806451612902,
  93.54838709677419,
  94.83870967741935,
  96.12903225806451,
  97.41935483870968,
  98.70967741935483,
  100.0,
};

void DriveServo::speed(int speed) {
  c_speed = speed;

  int raw;
  if (speed > 0) {
    //raw = map(speed, 1, SPEED_RANGE, c->dead_high, c->high);
    raw = round(c->dead_high + ((mapping[speed] / 100) * (c->high - c->dead_high)));
  } else if (speed < 0) {
    //raw = map(speed, -SPEED_RANGE, -1, c->low, c->dead_low);
    raw = round(c->dead_low - ((mapping[-speed] / 100) * (c->dead_low - c->low)));
  } else {
    raw = c->midpoint;
  }
  s.writeMicroseconds(raw);
}

