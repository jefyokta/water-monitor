#pragma once

inline void generateHTML(char* buffer, size_t len, float calib, float dist, const char* mqttHost) {
  const char* htmlTemplate = R"rawliteral(%.2f %.2f %s
)rawliteral";
  snprintf(buffer, len, htmlTemplate, calib, dist, mqttHost);
}