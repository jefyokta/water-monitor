#include "PHSensor.h"

float PHSensor::calibration = 21.3f;

PHSensor::PHSensor(int analogPin, int tempPin)
  : analogPin(analogPin), tempPin(tempPin), inTask(false) {}

void PHSensor::setCalibration(float value) {
  PHSensor::calibration = value;
}

void PHSensor::set(float maxAdc, float refVolt, float calibration) {
  this->maxAdc = maxAdc;
  this->refVoltage = refVolt;
  PHSensor::calibration = calibration;
}

float PHSensor::getValue() {

  for (int i = 0; i < SAMPLE_COUNT; i++) {

    samples[i] = analogRead(analogPin);


    inTask ? vTaskDelay(30) : delay(30);
  }
  this->sortSamples();

  float voltage = this->calculateVoltage();
  return this->convertVoltageToPH(voltage);
}

void PHSensor::sortSamples() {
  for (int i = 0; i < SAMPLE_COUNT - 1; i++) {
    for (int j = i + 1; j < SAMPLE_COUNT; j++) {
      if (samples[i] > samples[j]) {
        int tmp = samples[i];
        samples[i] = samples[j];
        samples[j] = tmp;
      }
    }
  }
}

float PHSensor::calculateVoltage() const {
  unsigned long sum = 0;
  for (int i = DISCARD_LOW; i < DISCARD_HIGH; i++) {
    sum += samples[i];
  }
  int count = DISCARD_HIGH - DISCARD_LOW;
  float avg = static_cast<float>(sum) / count;

  return (avg * this->refVoltage) / (this->maxAdc);
}

float PHSensor::convertVoltageToPH(float voltage) const {
  return -5.70f * voltage + PHSensor::calibration;
}

void PHSensor::calibrate() {
  float raw = analogRead(analogPin);
  Serial.print("Raw ADC Value: ");
  Serial.println(raw);
  Serial.print("Voltage: ");
  Serial.println(raw * (refVoltage / maxAdc));
}

void PHSensor::taskable() {
  this->inTask = true;
}

void PHSensor::untaskable() {
  this->inTask = false;
}

float PHSensor::getTemperature() {
  if (tempPin == -1) {
    Serial.println("Warning: Temperature pin is unset");
    return -1.0f;
  }
  return analogRead(tempPin);
}

void PHSensor::setCalibrationWithVolt(float volt) {

  PHSensor::calibration = 7.0 - (-5.7 * volt);
}

PHMembership PHSensor::membership() {
  float ph = this->getValue();
  PHMembership result;
  result.acidic = (ph < 7.0f) ? (7.0f - ph) / 7.0f : 0.0f;
  result.netral = (ph >= 6.5f && ph <= 7.5f) ? 1.0f : 0.0f;
  result.alkaline = (ph > 7.0f) ? (ph - 7.0f) / 7.0f : 0.0f;

  result.acidic = std::min(result.acidic, 1.0f);
  result.alkaline = std::min(result.alkaline, 1.0f);

  return result;
}

float PHSensor::getCalibration() {

  return PHSensor::calibration;
}
