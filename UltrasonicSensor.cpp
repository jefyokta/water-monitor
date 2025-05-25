#include "UltrasonicSensor.h"
#include <Arduino.h>


UltrasonicSensor::UltrasonicSensor(int trigPin,int echoPin) {
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  pinMode(this->trigPin, OUTPUT);
  pinMode(this->echoPin, INPUT);
}
float UltrasonicSensor::getValue() {
  long duration;
  this->trigger();
  duration = pulseIn(this->echoPin, HIGH);
  return duration * 0.034 / 2;
}

void UltrasonicSensor::trigger() {
  digitalWrite(this->trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->trigPin, LOW);
}