#include "weather_sensor.h"
#include <DHT.h>

const int DHT_PIN = 15;

DHT dht(DHT_PIN, DHT22);

void setupWeatherSensor() {
    dht.begin();
}

float measureTemperature() {
  return dht.readTemperature();
}

float measureHumidity() {
  return dht.readHumidity();
}
