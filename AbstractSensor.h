#pragma once

template<typename T>
class AbstractSensor {
protected:
  float down(const float x, const float bb, const float ba) {
    if ((ba - bb) == 0) return 0.0f;
    return (ba - x) / (ba - bb);
  }
  float up(const float x, const float bb, const float ba) {
    if ((ba - bb) == 0) return 0.0f;
    return (x - bb) / (ba - bb);
  }
  bool in(const float x, int range[2]) {
    return (x >= range[0] && x <= range[1]);
  }
  virtual T membership() = 0;
public:
  virtual float getValue() = 0;
  T getMembership() {
    return this->membership();
  }
};