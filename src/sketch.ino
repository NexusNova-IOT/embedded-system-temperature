#include <Arduino.h>
#include "wifi_utils.h"
#include "weather_sensor.h"
#include "http_utils.h"
#define DELAY 3000
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverAddress = "https://lifetravel-iot-backend.azurewebsites.net/api/v1/weather-sensors/update-weather/1";
const char* authToken = "eyJhbGciOiJSUzI1NiIsImtpZCI6ImQ0OWU0N2ZiZGQ0ZWUyNDE0Nzk2ZDhlMDhjZWY2YjU1ZDA3MDRlNGQiLCJ0eXAiOiJKV1QifQ.eyJpc3MiOiJodHRwczovL3NlY3VyZXRva2VuLmdvb2dsZS5jb20vbGlmZXRyYXZlbC1hcHAiLCJhdWQiOiJsaWZldHJhdmVsLWFwcCIsImF1dGhfdGltZSI6MTY5OTA3NTcxNCwidXNlcl9pZCI6IjJpRmNqeTJVaHhOdkJET1pNclFkMlZEb0lzeTIiLCJzdWIiOiIyaUZjankyVWh4TnZCRE9aTXJRZDJWRG9Jc3kyIiwiaWF0IjoxNjk5MDc1NzE0LCJleHAiOjE2OTkwNzkzMTQsImVtYWlsIjoiaW90QGdtYWlsLmNvbSIsImVtYWlsX3ZlcmlmaWVkIjpmYWxzZSwiZmlyZWJhc2UiOnsiaWRlbnRpdGllcyI6eyJlbWFpbCI6WyJpb3RAZ21haWwuY29tIl19LCJzaWduX2luX3Byb3ZpZGVyIjoicGFzc3dvcmQifX0.YR4dhjzf-JB96J-B1dLyq_YfxmALc4ufZIKQmg9-foUo7mPRnsA2DfZ4i7hlIWpBDRBtaqBJYRxRFvX8aCT5abxwKTc1rnEAjyMbSnOvQuJzzy34y6neNNHLK1wWt3nMTUti4kWWV2Gsw0Mcg5o1t3X2SQ9ZXD92w5ch0tYqqZxskFl-rPESL9rNX4Y1BS4D3V6_ma0IdtkcUW8J5bTOvQJw1wSAKrvOHQwI4j4yIQZq_uhXKhPdbdNYIG3wpYEvXLO9oX2R5yDuhx9CFOo6zpmiyUWbzuf_4ug1PgzL5d3tSVFa5CEdG2qzVTaMvJcUVsFOMymPMuqkNBPQ2ffGGQ";
// please update the token here
// https://iot-lifetravel-firebase-token-gen.netlify.app/login
// email: iot@gmail.com
// password: 12345678

void setup() {
  Serial.begin(115200);
  setupWiFi(ssid, password);
  setupWeatherSensor();
}

void loop() {
  float temperature = measureTemperature();
  float humidity = measureHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    String requestBody = String("{\"temperature\":") + temperature + ",\"humidity\":" + humidity + "}";
    Serial.println(requestBody);
    int httpResponseCode = sendPUTRequest(serverAddress, requestBody.c_str(), authToken);

    if (httpResponseCode == 200) {
      Serial.println("Actualizado con éxito en el servidor.");
    } else {
      Serial.print("Error en la solicitud. Código de respuesta HTTP: ");
      Serial.println(httpResponseCode);
    }
  } else {
    Serial.println("Error al leer los datos del sensor DHT.");
  }

  delay(DELAY);
}
