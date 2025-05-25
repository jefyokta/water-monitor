#pragma once

#define ULTRASONIC_SENSOR_H
#include "AbstractSensor.h"
#include <Arduino.h>


struct UltrasonicMembership {
  float deep;
  float surface;
};
class UltrasonicSensor : public AbstractSensor<UltrasonicMembership> {
private:
  int trigPin;
  int echoPin;
  void trigger();
public:
  UltrasonicSensor(int trigPin, int echoPin);
  float getValue() override;
};