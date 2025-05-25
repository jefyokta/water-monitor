#include "Fuzzy.h"
#include <algorithm>

float Fuzzy::min4(float a, float b, float c, float d) {
  return std::min({ a, b, c, d });
}

void Fuzzy::inference() {
  Rule r(4);

  r.when({ this->ph.netral, this->temp.normal, this->tds.low, this->ultra.deep }).conditionIs(static_cast<int>(WaterCondition::GOOD));

  for (const DefinedRule& rule : r.fulfilled()) {
    if (rule.condition == static_cast<int>(WaterCondition::BAD)) {
    }
  }
}
