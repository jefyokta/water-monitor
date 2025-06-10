#include "Rule.h"
#include <algorithm>
#include <stdexcept>
#include <string>

template<class T>
Rule<T>::Rule(int inputNum) {
  this->inputNum = inputNum;
}

template<class T>
Rule<T>& Rule<T>::when(const std::vector<float>& membershipVals) {
  if (membershipVals.size() != this->inputNum) {
    throw std::runtime_error(
      "Input rule must have " + std::to_string(this->inputNum) + " elements, but got " + std::to_string(membershipVals.size()));
  }
  this->currentRule.memberships = membershipVals;
  return *this;
}

template<class T>
void Rule<T>::conditionIs(T condition) {
  this->currentRule.condition = condition;
  this->rules.emplace_back(this->currentRule);
}

template<class T>
const std::vector<DefinedRule<T>>& Rule<T>::getRules() const {
  return this->rules;
}

template<class T>
std::vector<DefinedRule<T>> Rule<T>::fulfilled() const {
  std::vector<DefinedRule<T>> result;
  for (const DefinedRule<T>& rule : this->rules) {
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
