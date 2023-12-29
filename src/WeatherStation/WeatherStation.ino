/*
  MQTT and WiFi functions here are adapted from the simple client example at EspMQTTClient by @plapointe6.
  (https://github.com/plapointe6/EspMQTTClient/tree/master)


  Weather Station functions are adapted from the SparkFun MM_WeatherMeter_Test example.
  (https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/tree/master)


  I confess that it seems odd to put all of the main loop functionality inside the onConnectionEstablished() 
  loop here as my code using MQTT on Particle.io devices sets up the MQTT client in setup() 
  and allows you to put your logic and publish from the main loop.

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
int reportStride = 15000;   // report every 15 seconds
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
  Serial.println("Begin data collection!");

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

  while (1) {
    if (millis() - lastReport >= reportStride) {
    digitalWrite(LED_BUILTIN, HIGH);  //Blink stat LED
    //Get and print all readings every 5s
    printWeather();
    //Send wind speed to HA
    client.publish("ha/weather/windspeed", String(wind_speed));
    lastReport = millis();
  }

  digitalWrite(LED_BUILTIN, LOW);  //Turn off stat LED

  delay(100);
  }
}

void loop()
{
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
