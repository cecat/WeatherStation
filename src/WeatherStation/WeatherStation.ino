/*
  THIS CODE EXAMPLE is from EspMQTTClient by @plapointe6.
  (https://github.com/plapointe6/EspMQTTClient/tree/master)
  @cecat (12/29/23)

  SimpleMQTTClient.ino
  The purpose of this exemple is to illustrate a simple handling of MQTT and Wifi connection.
  
*/

#include "secrets.h"
#include "EspMQTTClient.h"

EspMQTTClient client(
  WIFI_SSID, WIFI_PWD,             // wifi ssid and password
  MQTT_BROKER, MQTT_USR, MQTT_PWD, // MQTT broker, username, password
  MQTT_CLIENT, 1883);		   // MQTT client name and port

int counter = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  
  // Subscribe to "ha/weather" and display received message to Serial
  client.subscribe("ha/weather", [](const String & payload) {
    Serial.println(payload);
  });

 // Publish a message to "ha/weather"
  client.publish("ha/weather", "let us begin"); // You can activate the retain flag by setting the third parameter to true

  while (counter < 10) {
    delay(2000);
    client.publish("ha/weather", String(counter));
    counter++;
  }
}

void loop()
{
  client.loop();

}
