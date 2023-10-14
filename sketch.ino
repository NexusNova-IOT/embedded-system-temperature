#include <WiFi.h>
#include <DHT.h>
#include <PubSubClient.h>
#define DELAY 1000
// MQTT Server Parameters
const char* MQTT_CLIENT_ID = "esp32-weather-demo";
const char* MQTT_BROKER = "broker.mqttdashboard.com";
const char* MQTT_USER = "";
const char* MQTT_PASSWORD = "";
const char* MQTT_TOPIC = "wokwi-weather";

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const int DHT_PIN = 15;

DHT dht(DHT_PIN, DHT22);
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  // Set up MQTT client
  client.setServer(MQTT_BROKER, 1883);

  // Initialize DHT sensor
  dht.begin();
}

void reconnect() {
  // Loop until we're reconnected to the MQTT broker
  while (!client.connected()) {
    Serial.print("Connecting to MQTT server... ");
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("Connected!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Measuring weather conditions
  Serial.print("Measuring weather conditions... ");
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    String message = String("{\"temp\":") + temperature + ",\"humidity\":" + humidity + "}";
    Serial.println("Updated!");
    Serial.print("Reporting to MQTT topic ");
    Serial.print(MQTT_TOPIC);
    Serial.print(": ");
    Serial.println(message);
    client.publish(MQTT_TOPIC, message.c_str());
  } else {
    Serial.println("Failed to read data from the DHT sensor.");
  }

  delay(DELAY);
}
