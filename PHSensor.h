#pragma once
#include "AbstractSensor.h"
#include <Arduino.h>


struct PHMembership {
  float acidic;
  float alkaline;
  float netral;
};
class PHSensor : public AbstractSensor<PHMembership> {
private:
  static constexpr int SAMPLE_COUNT = 10;
  static constexpr int DISCARD_LOW = 2;
  static constexpr int DISCARD_HIGH = 8;
  float refVoltage = 3.3f;
  float maxAdc = 4095.0;

  int analogPin;
  int tempPin;
  float calibration;
  int samples[SAMPLE_COUNT];
  bool inTask;

  void sortSamples();
  float calculateVoltage() const;
  float convertVoltageToPH(float voltage) const;

public:
  PHSensor(int analogPin, int tempPin = -1);
  void setCalibrationWithVolt(float volt);
  void setCalibration(float value);
  void set(float maxAdc, float refVolt, float calibration);

  float getValue() override;
  PHMembership membership() override;

  void calibrate();
  void taskable();
  void untaskable();

  float getTemperature();
};
