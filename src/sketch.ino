#include "wifi_utils.h"
#include "weather_sensor.h"
#include "http_utils.h"
#define DELAY 3000
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverAddress = "https://lifetravel-iot-backend.azurewebsites.net/api/v1/weather-sensors/update-weather/1";
const char* authToken = "Bearer eyJhbGciOiJSUzI1NiIsImtpZCI6ImQ0OWU0N2ZiZGQ0ZWUyNDE0Nzk2ZDhlMDhjZWY2YjU1ZDA3MDRlNGQiLCJ0eXAiOiJKV1QifQ.eyJpc3MiOiJodHRwczovL3NlY3VyZXRva2VuLmdvb2dsZS5jb20vbGlmZXRyYXZlbC1hcHAiLCJhdWQiOiJsaWZldHJhdmVsLWFwcCIsImF1dGhfdGltZSI6MTY5OTM3NDk2OSwidXNlcl9pZCI6IjJpRmNqeTJVaHhOdkJET1pNclFkMlZEb0lzeTIiLCJzdWIiOiIyaUZjankyVWh4TnZCRE9aTXJRZDJWRG9Jc3kyIiwiaWF0IjoxNjk5Mzc0OTY5LCJleHAiOjE2OTkzNzg1NjksImVtYWlsIjoiaW90QGdtYWlsLmNvbSIsImVtYWlsX3ZlcmlmaWVkIjpmYWxzZSwiZmlyZWJhc2UiOnsiaWRlbnRpdGllcyI6eyJlbWFpbCI6WyJpb3RAZ21haWwuY29tIl19LCJzaWduX2luX3Byb3ZpZGVyIjoicGFzc3dvcmQifX0.IvrGpcMFrBCgQkWGsDSfBR99DrI3U66l5y89KAgFkiHVQjuPCIUUP2rG5Y40smOBx9VmZGaDOPpEcJiVoQR7aH7AJcH3K8kIienC9cxVhsp3xPYEOJ6_yNK34vi8bP8n7tsOQIAk65a-xrFR2EtnNe2318DAqrsBFu0ArKpnzw597-zjRj3o2tIoTrvzNW1IbKuTjKfUsgiKoy6orMnB944gP5IN2y2T7lHZZ40N5DYn4VeDkS37t6pY5aVWLfg8dDT0Hr_dInxRIll2JuGohLt6bHW1-bBkfy4e1VBoB5JuNy1R9gglCruda2XMIhDMA53MV4NuI4zFsWePh08U6Q";
// please update the token here
// https://iot-lifetravel-firebase-token-gen.netlify.app
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
