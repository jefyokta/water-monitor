#include "Rule.h"
#include <algorithm>
#include <stdexcept>
#include <string>

Rule::Rule(int inputNum) {
  this->inputNum = inputNum;
}
Rule& Rule::when(const std::vector<float>& membershipVals) {
  if (membershipVals.size() != this->inputNum) {
    throw std::runtime_error(
      "Input rule must have " + std::to_string(this->inputNum) + " elements, but got " + std::to_string(membershipVals.size()));
  }
  this->currentRule.memberships = membershipVals;
  return *this;
}
void Rule::conditionIs(const int condition) {
  this->currentRule.condition = condition;
  this->rules.emplace_back(this->currentRule);
}

const std::vector<DefinedRule>& Rule::getRules() const {
  return this->rules;
}

std::vector<DefinedRule> Rule::fulfilled() const {
  std::vector<DefinedRule> result;

  for (const DefinedRule& rule : this->rules) {
    bool hasZero = std::any_of(
      rule.memberships.begin(),
      rule.memberships.end(),
      [](float v) {
        return v == 0.0f;
      });

    if (!hasZero) {
      result.push_back(rule);
    }
  }

  return result;
}
