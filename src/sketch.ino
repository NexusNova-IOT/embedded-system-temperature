#include "Arduino.h"
#include "wifi_utils.h"
#include "weather_sensor.h"
#include "http_utils.h"
#define DELAY 500
String authToken;
void setup() {
  Serial.begin(115200);
  setupWiFi();
  //authToken = authAndGetToken();
  authToken = "eyJhbGciOiJSUzI1NiIsImtpZCI6ImE2YzYzNTNmMmEzZWMxMjg2NTA1MzBkMTVmNmM0Y2Y0NTcxYTQ1NTciLCJ0eXAiOiJKV1QifQ.eyJpc3MiOiJodHRwczovL3NlY3VyZXRva2VuLmdvb2dsZS5jb20vbGlmZXRyYXZlbC1hcHAiLCJhdWQiOiJsaWZldHJhdmVsLWFwcCIsImF1dGhfdGltZSI6MTcwMDE3NTU1NiwidXNlcl9pZCI6IjJpRmNqeTJVaHhOdkJET1pNclFkMlZEb0lzeTIiLCJzdWIiOiIyaUZjankyVWh4TnZCRE9aTXJRZDJWRG9Jc3kyIiwiaWF0IjoxNzAwMTc1NTU2LCJleHAiOjE3MDAxNzkxNTYsImVtYWlsIjoiaW90QGdtYWlsLmNvbSIsImVtYWlsX3ZlcmlmaWVkIjpmYWxzZSwiZmlyZWJhc2UiOnsiaWRlbnRpdGllcyI6eyJlbWFpbCI6WyJpb3RAZ21haWwuY29tIl19LCJzaWduX2luX3Byb3ZpZGVyIjoicGFzc3dvcmQifX0.X4AWzFcKFRhiX0Q40w03T90TdjWqBAtgGXHglveHPnqAVcLw7DD2C4P2kWRsujSF0us0pPWtEpO9Q7HO8nCcz-rkEimvgKcZtjhTIZJ4fDbKsDVIbiVNF8yLge8O7DBEueoKIbUtoGiH0rJzjlN0C0mJ2w1HDJv3C7_6PvIvdi5gXQUJbZH05cAbMCuH4PU7pBMZDCHFh-E8wz5_m54o6s4TxNEJz-dmVJ7gi8QS-uMzlwKVDAkDFu_9VtJ8ICDFEpAbQaGjW0dBT8DkFlaF7i_fIva7Ff3ecMvQCsv0DohRp5exASf2evn4l2e3xfm_GERFuWEsM8pQmDB6M3Q89Q";
  setupWeatherSensor();
}

void loop() {
  float temperature = measureTemperature();
  float humidity = measureHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    String requestBody = String("{\"temperature\":") + temperature + ",\"humidity\":" + humidity + "}";
    Serial.println(requestBody);
    int httpResponseCode = sendPUTRequest(requestBody.c_str(), authToken.c_str());
    checkResponseCode(httpResponseCode);
  }
  delay(DELAY);
}
