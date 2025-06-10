#include "DissolvedSolid.h"
#include <Arduino.h>
#include <cstring>
#include <algorithm>
#include <cmath>


DissolvedSolid::DissolvedSolid(int pin, bool taskable) {
  this->pin = pin;
  this->taskable = taskable;
  std::memset(this->buffer, 0, sizeof(this->buffer));
}

void DissolvedSolid::fillBuffer() {
  this->buffer[this->bufferIndex] = analogRead(this->pin);
  this->bufferIndex = (this->bufferIndex + 1) % SCOUNT;
}

float DissolvedSolid::getPPM() {
  int temp[SCOUNT];
  std::memcpy(temp, this->buffer, sizeof(temp));
  std::sort(temp, temp + SCOUNT);

  int sum = 0;
  for (int i = 5; i < SCOUNT - 5; i++) {
    sum += temp[i];
  }

  float avgADC = static_cast<float>(sum) / (SCOUNT - 10);
  float voltage = (avgADC * this->vref) / 4095.0;

  float compVolt = voltage / 1.0;
  float ppm = (133.42 * pow(compVolt, 3) - 255.86 * pow(compVolt, 2) + 857.39 * compVolt) * 0.5;
  return ppm;
}

float DissolvedSolid::getValue() {
  for (int i = 0; i < SCOUNT; i++) {
    this->fillBuffer();
    this->taskable ? vTaskDelay(40 / portTICK_PERIOD_MS) : delayMicroseconds(40000);
  }

  return this->getPPM();
}


DissolvedMembership DissolvedSolid::membership() {
  DissolvedMembership d;
  d.high = 0;
  d.low = 0;
  d.medium = 0;
  return d;
}
