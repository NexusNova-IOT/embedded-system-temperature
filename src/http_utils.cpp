#include "http_utils.hpp"
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* authServerAddress = "https://lifetravel-iot-api.azurewebsites.net/iot/logger/token";
const char* serverAddress= "https://lifetravel-iot-api.azurewebsites.net/api/v1/weather-sensors/update-weather/";

const char* authAndGetToken(const char* email, const char* password) {
  Serial.println("Waiting for the authentication response...");

  // Create HTTP client
  HTTPClient http;
  http.setTimeout(10000);
  http.begin(authServerAddress);
  http.addHeader("Content-Type", "application/json");

  // Prepare authentication request body
  String requestBody = "{\"email\":\"" + String(email) + "\",\"password\":\"" + String(password) + "\"}";

  // Send authentication request
  int httpResponseCode = http.POST(requestBody);
  String token = "";

  if (httpResponseCode == 200) {
    // Parse the JSON response to extract the authorization token
    String response = http.getString();
    const size_t capacity = JSON_OBJECT_SIZE(10) + 1024;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, response);

    token = doc["idToken"].as<String>();
    http.end();
    Serial.println("Successful authentication");
    return token.c_str();
  } else {
    // Handle authentication error
    Serial.print("Authentication Error. HTTP response code:");
    Serial.println(httpResponseCode);
    http.end();
    Serial.println("An error occurred during authentication");
    return nullptr;
  }
}

// Function to send a PUT request to update data on the server
int sendUpdateRequest(const char* requestBody, const char* authToken, int resourceId) {
  // Create an HTTP client instance
  HTTPClient http;
  http.begin(serverAddress + String(resourceId));

  // Set headers for JSON data and authorization
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(authToken));

  // Send the PUT request and get the HTTP response code
  int httpResponseCode = http.PUT(requestBody);

  // Print the server response for debugging
  Serial.println(http.getString());
  http.end();

  // Return the HTTP response code
  return httpResponseCode;
}

// Function to check and print the HTTP response code
void checkResponseCode(int httpResponseCode) {
  // Check if the response code indicates success (HTTP 200 OK)
  if (httpResponseCode == 200) {
    Serial.println("Update successful on the server.");
  } else {
    // Print an error message with the HTTP response code
    Serial.print("Request error. HTTP response code:");
    Serial.println(httpResponseCode);
  }
}