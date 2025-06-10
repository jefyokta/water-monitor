#include "UltrasonicSensor.h"
#include <Arduino.h>

float UltrasonicSensor::baseDistance = 50.0f;
UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin) {
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  pinMode(this->trigPin, OUTPUT);
  pinMode(this->echoPin, INPUT);
}

float UltrasonicSensor::getBaseDistance() {
  return UltrasonicSensor::baseDistance;
}
float UltrasonicSensor::getValue() {

  return UltrasonicSensor::baseDistance - this->getWaterDistance();
}

void UltrasonicSensor::trigger() {
  digitalWrite(this->trigPin, LOW);
  ets_delay_us(2);
  digitalWrite(this->trigPin, HIGH);
  ets_delay_us(20);
  digitalWrite(this->trigPin, LOW);
}

float UltrasonicSensor::getWaterDistance() {
  long duration;
  this->trigger();
  duration = pulseIn(this->echoPin, HIGH, 30000);
  if (duration == 0 || duration > 25000) {
    Serial.println("[Ultrasonic] Gagal baca (timeout)");
    return -1.0f;
  }
  return duration * 0.034 / 2;
}
void UltrasonicSensor::setBaseDistance(const float distance) {
  UltrasonicSensor::baseDistance = distance;
}

UltrasonicMembership UltrasonicSensor::membership() {
  UltrasonicMembership d;
  d.deep = 0;
  d.surface = 0;
  return d;
}