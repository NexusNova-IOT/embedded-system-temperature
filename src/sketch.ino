#include "Arduino.h"
#include "wifi_utils.hpp"
#include "weather_sensor.hpp"
#include "http_utils.hpp"
#define DELAY 500
#define DEVICE_ID 1

String authToken;

void setup() {
  Serial.begin(115200);

  // Initialize WiFi connection
  setupWiFi();

  // Authenticate and get the authorization token
  authToken = authAndGetToken();
  
  // Initialize weather sensor
  setupWeatherSensor();
}

void loop() {
  // Measure temperature and humidity
  float temperature = measureTemperature();
  float humidity = measureHumidity();

  // Check if the measurements are valid
  if (!isnan(temperature) && !isnan(humidity)) {
    // Create JSON payload with temperature and humidity
    String requestBody = String("{\"temperature\":") + temperature + ",\"humidity\":" + humidity + "}";
    Serial.println(requestBody);

    // Send the data to the server using a PUT request
    int httpResponseCode = sendUpdateRequest(requestBody.c_str(), authToken.c_str(), DEVICE_ID);

    // Check the server response
    checkResponseCode(httpResponseCode);
  }

  // Delay before the next iteration
  delay(DELAY);
}
