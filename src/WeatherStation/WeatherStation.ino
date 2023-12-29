/*
  MQTT and WiFi functions here are adapted from the simple client example at EspMQTTClient by @plapointe6.
  (https://github.com/plapointe6/EspMQTTClient/tree/master)


  Weather Station functions are adapted from the SparkFun MM_WeatherMeter_Test example.
  (https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/tree/master)

  @cecat (12/29/23)
  
*/

#include "secrets.h"
#include "EspMQTTClient.h"

#include "SparkFun_Weather_Meter_Kit_Arduino_Library.h"  //http://librarymanager/All#SparkFun_Weather_Meter_Kit
//Hardware pin definitions
const byte WSPEED = 14;     //Digital I/O pin for wind speed
const byte WDIR = 35;       //Analog pin for wind direction
const byte RAIN = 27;       //Digital I/O pin for rain fall
//Global Variables
long lastReport;            //Last time we reported so we can time the next report
int reportStride = 45000;   // report every reportStride ms (5 min = 300k)
float wind_dir = 0;         // [degrees (Cardinal)]
float wind_speed = 0;       // [kph]
float rain = 0;             // [mm]

SFEWeatherMeterKit myweatherMeterKit(WDIR, WSPEED, RAIN);  // Create an instance of the weather meter kit


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
  //client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  //client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  //client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true

  myweatherMeterKit.setADCResolutionBits(10);
  myweatherMeterKit.begin();
  lastReport = 0;
  Serial.println("Begin weather data collection!");

}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  
  // Subscribe to "ha/wind/speed" and display received message to Serial
  client.subscribe("ha/wind/speed", [](const String & payload) {
    Serial.println(payload);
  });
    // Subscribe to "ha/wind/dir" and display received message to Serial
  client.subscribe("ha/wind/dir", [](const String & payload) {
    Serial.println(payload);
  });
    // Subscribe to "ha/rain/total" and display received message to Serial
  client.subscribe("ha/rain/total", [](const String & payload) {
    Serial.println(payload);
  });

}

void loop()
{
  if (millis() - lastReport >= reportStride){
    printWeather();
    lastReport = millis();
    client.publish("ha/wind/speed", String(wind_speed));
    delay(500);
    client.publish("ha/wind/dir", String(wind_dir));
    delay(500);
    client.publish("ha/rain/total", String(rain));
  }
  client.loop();

}

//Calculates data from weather meter kit 
void calcWeather() {

  //Weather Meter Kit
  //Calc Wind
  wind_dir = myweatherMeterKit.getWindDirection();
  wind_speed = myweatherMeterKit.getWindSpeed();
  //Calc Rain
  rain = myweatherMeterKit.getTotalRainfall();
}
//Print the variables to serial
void printWeather() {
  calcWeather();  //Go calc all the various sensors

  Serial.println();
  Serial.print("wind direction= ");
  Serial.print(wind_dir, 1);
  Serial.print(" deg, wind speed= ");
  Serial.print(wind_speed, 1);
  Serial.print(" kph, total rain= ");
  Serial.print(rain, 1);
  Serial.println(" mm");
}
