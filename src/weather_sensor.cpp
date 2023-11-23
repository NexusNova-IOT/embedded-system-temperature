#include "weather_sensor.hpp"
#include <DHT.h>

const int DHT_PIN = 15;

DHT dht(DHT_PIN, DHT22);

void setupWeatherSensor() {
    // Initialize the DHT sensor
    dht.begin();
}

float measureTemperature() {
  // Read and return the temperature from the DHT sensor
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Error reading temperature.");
  }
  return temperature;
}

float measureHumidity() {
  // Read and return the humidity from the DHT sensor
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("Error reading humidity.");
  }
  return humidity;
}
