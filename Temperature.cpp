#include "Temperature.h"

TemperatureSensor::TemperatureSensor(DallasTemperature& tmp) {
  this->tmp = &tmp;
  this->tmp->begin();
}
float TemperatureSensor::getValue() {
  this->tmp->requestTemperatures();
  return this->tmp->getTempCByIndex(0);
}
TemperatureMembership TemperatureSensor::membership() {
  TemperatureMembership t;
  float val = this->getValue();
  t.cold = this->getColdMembership(val);
  t.normal = this->getNormalMembership(val);
  t.hot = this->getHotMembership(val);
  return t;
}

float TemperatureSensor::getColdMembership(const float val) {
  if (!this->in(val, this->coldRange)) {
    return 0.0f;
  }
  if (this->in(val, this->normalRange)) {
    return this->up(val, this->normalRange[0], this->coldRange[1]);
  }
  return 1.0f;
}

float TemperatureSensor::getNormalMembership(const float val) {
  if (!this->in(val, this->normalRange)) return 0.0f;
  if (this->in(val, this->coldRange)) {
    return this->down(val, this->normalRange[0], this->coldRange[1]);
  }
  if (this->in(val, this->hotRange)) {
    return this->up(val, this->hotRange[0], this->normalRange[1]);
  }
  return 1.0f;
}

float TemperatureSensor::getHotMembership(const float val) {
  if (!this->in(val, this->hotRange)) return 0.0f;
  if (this->in(val, this->normalRange)) {
    return this->down(val, this->hotRange[0], this->normalRange[1]);
  }

  return 1.0f;
}