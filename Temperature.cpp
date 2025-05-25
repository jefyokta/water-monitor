#include "Temperature.h"

TemperatureSensor::TemperatureSensor(DallasTemperature& tmp) {
  this->tmp = &tmp;
  this->tmp->begin();
}
float TemperatureSensor::getValue() {
  this->tmp->requestTemperatures();
  return this->tmp->getTempCByIndex(0);
}