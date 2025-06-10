#include "Fuzzy.h"
#include <algorithm>

float Fuzzy::min4(float a, float b, float c, float d) {
  return std::min({ a, b, c, d });
}

void Fuzzy::inference() {
  Rule<WaterCondition> r(4);

  PHMembership mPH = this->ph->getMembership();
  TemperatureMembership mTemp = this->temp->getMembership();
  UltrasonicMembership mUltra = this->ultra->getMembership();
  DissolvedMembership mTds = this->tds->getMembership();

  r.when({ mPH.acidic, mTemp.hot, mUltra.deep, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.hot, mUltra.deep, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.hot, mUltra.deep, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.acidic, mTemp.hot, mUltra.surface, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.hot, mUltra.surface, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.hot, mUltra.surface, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.acidic, mTemp.cold, mUltra.deep, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.cold, mUltra.deep, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.cold, mUltra.deep, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.acidic, mTemp.cold, mUltra.surface, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.cold, mUltra.surface, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.cold, mUltra.surface, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.acidic, mTemp.normal, mUltra.deep, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.normal, mUltra.deep, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.normal, mUltra.deep, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.acidic, mTemp.normal, mUltra.surface, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.normal, mUltra.surface, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.acidic, mTemp.normal, mUltra.surface, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.alkaline, mTemp.hot, mUltra.deep, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.hot, mUltra.deep, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.hot, mUltra.deep, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.alkaline, mTemp.hot, mUltra.surface, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.hot, mUltra.surface, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.hot, mUltra.surface, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.alkaline, mTemp.cold, mUltra.deep, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.cold, mUltra.deep, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.cold, mUltra.deep, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.alkaline, mTemp.cold, mUltra.surface, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.cold, mUltra.surface, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.cold, mUltra.surface, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.alkaline, mTemp.normal, mUltra.deep, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.normal, mUltra.deep, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.normal, mUltra.deep, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.alkaline, mTemp.normal, mUltra.surface, mTds.low }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.normal, mUltra.surface, mTds.medium }).conditionIs(WaterCondition::BAD);
  r.when({ mPH.alkaline, mTemp.normal, mUltra.surface, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.netral, mTemp.hot, mUltra.deep, mTds.low }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.hot, mUltra.deep, mTds.medium }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.hot, mUltra.deep, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.netral, mTemp.hot, mUltra.surface, mTds.low }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.hot, mUltra.surface, mTds.medium }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.hot, mUltra.surface, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.netral, mTemp.cold, mUltra.deep, mTds.low }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.cold, mUltra.deep, mTds.medium }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.cold, mUltra.deep, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.netral, mTemp.cold, mUltra.surface, mTds.low }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.cold, mUltra.surface, mTds.medium }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.cold, mUltra.surface, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.netral, mTemp.normal, mUltra.deep, mTds.low }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.normal, mUltra.deep, mTds.medium }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.normal, mUltra.deep, mTds.high }).conditionIs(WaterCondition::BAD);

  r.when({ mPH.netral, mTemp.normal, mUltra.surface, mTds.low }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.normal, mUltra.surface, mTds.medium }).conditionIs(WaterCondition::GOOD);
  r.when({ mPH.netral, mTemp.normal, mUltra.surface, mTds.high }).conditionIs(WaterCondition::BAD);


  for (const DefinedRule<WaterCondition>& rule : r.fulfilled()) {
    if (rule.condition == WaterCondition::BAD) {
    }
  }
}

Fuzzy::Fuzzy(PHSensor& ph,
             TemperatureSensor& temp,
             UltrasonicSensor& ultra,
             DissolvedSolid& tds) {
  this->ph = &ph;
  this->temp = &temp;
  this->ultra = &ultra;
  this->tds = &tds;
}
