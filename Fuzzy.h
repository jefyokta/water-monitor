#pragma once

#include "Rule.h"
#include "Temperature.h"
#include "UltrasonicSensor.h"
#include "DissolvedSolid.h"
#include "PHSensor.h"

enum class WaterCondition {
  GOOD,
  BAD
};

class Fuzzy {
public:
  void inference();
  float defuzzy();
  Fuzzy(PHSensor& ph,
        TemperatureSensor& temp,
        UltrasonicSensor& ultra,
        DissolvedSolid& tds);
private:
  PHSensor* ph;
  TemperatureSensor* temp;
  UltrasonicSensor* ultra;
  DissolvedSolid* tds;
  float min4(float a, float b, float c, float d);
};
