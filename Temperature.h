#pragma once
#include "AbstractSensor.h"
#include <DallasTemperature.h>


struct TemperatureMembership {
  float hot;
  float cold;
  float normal;
};
class TemperatureSensor : public AbstractSensor<TemperatureMembership> {
private:
  int coldRange[2];
  int normalRange[2];
  int hotRange[2];
  DallasTemperature* tmp;
  float getHotMembership(const float val);
  float getColdMembership(const float val);
  float getNormalMembership(const float val);
protected:
  TemperatureMembership membership() override;
public:
  TemperatureSensor(DallasTemperature& tmp);
  float getValue() override;
};