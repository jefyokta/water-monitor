#pragma once

#include <vector>
#include <stdexcept>

struct DefinedRule {
  std::vector<float> memberships;
  int condition;
};

class Rule {
private:
  std::vector<DefinedRule> rules;
  DefinedRule currentRule;
  int inputNum;

public:
  Rule(int inputNum); 
  Rule& when(const std::vector<float>& membershipVals);
  void conditionIs(const int condition);
  const std::vector<DefinedRule>& getRules() const;
  std::vector<DefinedRule> fulfilled() const;
};
