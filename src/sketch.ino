#include "Arduino.h"
#include "wifi_utils.hpp"
#include "weather_sensor.hpp"
#include "http_utils.hpp"
#define DELAY 500
#define DEVICE_ID 1

String authToken;

void setup() {
  Serial.begin(115200);
  setupWiFi();
  authToken = authAndGetToken();
  Serial.println(authToken);
  setupWeatherSensor();
}

void loop() {
  float temperature = measureTemperature();
  float humidity = measureHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    String requestBody = String("{\"temperature\":") + temperature + ",\"humidity\":" + humidity + "}";
    Serial.println(requestBody);
    int httpResponseCode = sendPUTRequest(requestBody.c_str(), authToken.c_str(), DEVICE_ID);
    checkResponseCode(httpResponseCode);
  }
  delay(DELAY);
}
