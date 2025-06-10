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
  static float baseDistance;
  void trigger();
protected:
  UltrasonicMembership membership() override;
public:
  UltrasonicSensor(int trigPin, int echoPin);
  void setBaseDistance(const float distance);
  float getWaterDistance();
  float getValue() override;

  float getBaseDistance();
};