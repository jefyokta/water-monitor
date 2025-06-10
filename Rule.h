#pragma once

#include <vector>
#include <stdexcept>

template<typename T>
struct DefinedRule {
  std::vector<float> memberships;
  T condition;
};

template<typename T>
class Rule {
private:
  std::vector<DefinedRule<T>> rules;
  DefinedRule<T> currentRule;
  int inputNum;

public:
  Rule(int inputNum);
  Rule<T>& when(const std::vector<float>& membershipVals);
  void conditionIs(T condition);
  const std::vector<DefinedRule<T>>& getRules() const;
  std::vector<DefinedRule<T>> fulfilled() const;
};
