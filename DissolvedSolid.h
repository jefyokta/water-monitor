#pragma once
#include "AbstractSensor.h"

#define DISSOLVED_H

struct DissolvedMembership {
  float low;
  float medium;
  float high;
};

class DissolvedSolid : public AbstractSensor<DissolvedMembership> {
private:
  static constexpr int SCOUNT = 30;
  int pin;
  float vref = 3.3;
  int buffer[SCOUNT];
  int bufferIndex = 0;
  float lastPPM = 0;
  bool taskable = true;
protected:
  DissolvedMembership membership() override;
public:
  DissolvedSolid(int pin, bool taskable);
  void fillBuffer();
  float getPPM();
  float getValue() override;
};