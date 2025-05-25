#include "PHSensor.h"
#include "Preferences.h"


PHSensor phsensor(34);
void setup() {
  Serial.begin(115200);
}

void loop() {
  phsensor.calibrate();
  Serial.printf("PH: %.2f\n", phsensor.getValue());
  delay(500);
}
