#pragma once
#include "AbstractSensor.h"

struct DissolvedMembership
{
  float low;
  float medium;
  float high;
};
class DissolvedSolid : public AbstractSensor<DissolvedMembership>
{
private:
  float vref = 3.3;
  int pin;

public:
  DissolvedSolid(int pin);
  float getPPM();
  void calibrate();
};