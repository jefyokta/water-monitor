#pragma once

#define ABSTRACT_SENSOR_H
template<typename T>
class AbstractSensor {
public:
  virtual float getValue() = 0;

  virtual T membership() = 0;
};