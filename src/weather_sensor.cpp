#include "weather_sensor.h"
#include <DHT.h>

const int DHT_PIN = 15;

DHT dht(DHT_PIN, DHT22);

void setupWeatherSensor() {
    dht.begin();
}

float measureTemperature() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Error reading temperature.");
  }
  return temperature;
}

float measureHumidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("Error reading humidity.");
  }
  return humidity;
}
