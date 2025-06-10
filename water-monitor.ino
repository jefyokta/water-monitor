#include "PHSensor.h"
#include "Preferences.h"
#include "ESPAsyncWebServer.h"
#include "Temperature.h"
#include "DissolvedSolid.h"
#include "UltrasonicSensor.h"
#include "DallasTemperature.h"
#include "WiFi.h"
#include "WebSocketsClient.h"
#include <OneWire.h>
#include "GravityTDS.h"
#include "ArduinoJson.h"

#define TDS_PIN 27
Preferences pref;
//sensor conf
float distance = 20.0f;
float calibrationValue = 21.3f;
//sensor classes
PHSensor phsensor(34);
GravityTDS tds;
OneWire oneWire(25);
DallasTemperature tmp(&oneWire);
TemperatureSensor temp(tmp);
UltrasonicSensor ultra(5, 18);
//server
String serverHost = "192.168.149.77";
uint64_t serverPort = 8000;
WebSocketsClient ws;


typedef struct {
  float ph;
  float temp;
  float deep;
  float tds;
} SensorData;

typedef struct {
  float base;
  float calibration;
} ConfData;

//kiu
QueueHandle_t sensorQueue;
QueueHandle_t confQueue;



void setup() {
  Serial.begin(115200);
  setupPreference();
  setupWifi();
  setupClient();
  sensorQueue = xQueueCreate(5, sizeof(SensorData));
  confQueue = xQueueCreate(5, sizeof(ConfData));
  xTaskCreate(wsTask, "wsTask", 4096, NULL, 1, NULL);
  xTaskCreate(messageTask, "msgTask", 4096, NULL, 1, NULL);
  xTaskCreate(sensorTask, "sensorTask", 4096, NULL, 1, NULL);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(2000));
}



void setupWifi() {
  pref.begin("water", true);
  String ssid = pref.getString("ssid", "jefkulbet");
  String pass = pref.getString("pass", "1234567890");
  pref.end();
  WiFi.begin(ssid.c_str(), pass.c_str());
  WiFi.setHostname("Esp32WaterMonitor");
}

void setupClient() {
  pref.begin("water");
  serverHost = pref.getString("host", serverHost);
  serverPort = pref.getUShort("port", serverPort);
  pref.end();
  ws.setReconnectInterval(5000);

  ws.begin(serverHost, serverPort, "/?token=secret");
  ws.onEvent(webSocketEvent);
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("[WebSocket] Connected to server");
      break;
    case WStype_DISCONNECTED:
      // Serial.println("[WebSocket] Disconnected");
      break;
    case WStype_TEXT:
      Serial.printf("[WebSocket] Received text: %s\n", payload);
      char buffer[256];
      infoJson(buffer, sizeof(buffer));
      ws.sendTXT(buffer);
      break;
  }
}
void handleMessage(const char* message) {
  char response[256];
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, message);
  if (err) {
    snprintf(response, sizeof(response),
             R"({"event":"esp_info","message":"Invalid JSON"})");
    ws.sendTXT(response);
    return;
  }
  const char* event = doc["event"];
  if (strcmp(event, "conf") == 0) {
    float kVal = doc["message"]["kVal"].as<float>();
    float kTemp = doc["message"]["kTemp"].as<float>();
    tds.calibrate(kVal, kTemp);

    snprintf(response, sizeof(response),
             R"({"event":"esp_info","message":"TDS calibrated!"})");

  } else if (strcmp(event, "calibration") == 0) {
    float calibration = doc["message"]["calibration"].as<float>();
    float distance = doc["message"]["distance"].as<float>();
    phsensor.setCalibration(calibration);
    ultra.setBaseDistance(distance);

    snprintf(response, sizeof(response),
             R"({"event":"esp_info","message":"pH & distance changed!"})");
  } else {
    snprintf(response, sizeof(response),
             R"({"event":"esp_info","message":"Unknown event!"})");
  }

  ws.sendTXT(response);
}


void infoJson(char* buffer, size_t size) {
  snprintf(buffer, sizeof(buffer), R"({"event":"ip" ,"message":{"ip":"%s","tds_cal":"%.2f","ph_cal":"%.2f"}})",
           WiFi.localIP().toString().c_str(),
           tds.getKvalue(),
           phsensor.getCalibration());
}

void wsTask(void* p) {
  for (;;) {
    ws.loop();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
void messageTask(void* p) {
  SensorData bufferData;
  char jsonBuffer[256];
  for (;;) {
    if (xQueueReceive(sensorQueue, &bufferData, pdMS_TO_TICKS(100))) {
      json(jsonBuffer, sizeof(jsonBuffer), bufferData);
      ws.sendTXT(jsonBuffer);
    }
  }
}


void setupPreference() {
  pref.begin("water");
  float cal = pref.getFloat("calibration", 23.34f);
  float dis = pref.getFloat("distance", 20.0f);
  pref.end();
  tds.setPin(TDS_PIN);
  tds.setAref(3.3);
  tds.setAdcRange(4096);
  tds.begin();
  phsensor.setCalibration(cal);
  ultra.setBaseDistance(dis);
}

void sensorTask(void* pv) {
  ConfData d;
  float tempVal;
  while (1) {
    if (xQueueReceive(confQueue, &d, 0)) {
      phsensor.setCalibration(d.calibration);
      ultra.setBaseDistance(d.base);
    };
    // Serial.printf("distance between ultrasonic sensor to base of pond: %.2f cm\n", ultra.getBaseDistance());
    tempVal = temp.getValue();
    tds.setTemperature(tempVal);
    tds.update();
    SensorData data = {
      .ph = phsensor.getValue(),
      .temp = temp.getValue(),
      .deep = ultra.getWaterDistance(),
      .tds = tds.getTdsValue()
    };
    Serial.printf("SensorData => pH: %.2f, Temp: %.2f°C, Kedalaman: %.2f cm, TDS: %.2f ppm\n",
                  data.ph, data.temp, data.deep, data.tds);
    xQueueSend(sensorQueue, &data, portMAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void json(char* buffer, size_t size, SensorData& data) {
  snprintf(buffer, size,
           R"({"event":"publish","message":{"ph":%.2f,"deep":%.2f,"temp":%.2f,"tds":%.2f}})",
           data.ph, data.deep, data.temp, data.tds);
}
