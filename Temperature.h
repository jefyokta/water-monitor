#pragma once
#define TEMPERATURE_SENSOR_H
#include "AbstractSensor.h"
#include <DallasTemperature.h>


struct TemperatureMembership {
  float hot;
  float cold;
  float normal;
};
class TemperatureSensor : public AbstractSensor<TemperatureMembership> {
private:
  DallasTemperature* tmp;
public:
  TemperatureSensor(DallasTemperature& tmp);
  float getValue() override;
};