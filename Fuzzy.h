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


private:
  PHMembership ph;
  TemperatureMembership temp;
  UltrasonicMembership ultra;
  DissolvedMembership tds;
  float min4(float a, float b, float c, float d);
};
