/*
  MQTT and WiFi functions here are adapted from the simple client
  example at EspMQTTClient by @plapointe6.
  (https://github.com/plapointe6/EspMQTTClient/tree/master)


  Weather Station functions are adapted from the SparkFun
  MM_WeatherMeter_Test example.
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
float wind_dir = 0;         // [degrees (Cardinal)]
float wind_speed = 0;       // [kph]
float rain = 0;             // [mm]
bool goTime = false;        // did the timer fire?

// Create an instance of the weather meter kit
SFEWeatherMeterKit myweatherMeterKit(WDIR, WSPEED, RAIN);  

// Create a WiFi/MQTT client
EspMQTTClient client(
  WIFI_SSID, WIFI_PWD,             // wifi ssid and password
  MQTT_BROKER, MQTT_USR, MQTT_PWD, // MQTT broker, username, password
  MQTT_CLIENT, 1883);		           // MQTT client name and port

// Set an interrupt timer to check and report weather data
// A nice tutorial on ESP32 timers:
// https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts

int weatherCheckFreq = 30000000; // interval to check and report (in usecs)
hw_timer_t *Wc_timer = NULL;

// interrupt handler
void IRAM_ATTR onNudge() {
  goTime = true;
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  //client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  //client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  //client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true

  // set up interrupt timer
  Wc_timer = timerBegin(0, 80, true);   // set timer to count in microsecs 
  timerAttachInterrupt(Wc_timer, &onNudge, true); 
  timerAlarmWrite(Wc_timer, weatherCheckFreq, true);
  timerAlarmEnable(Wc_timer);
  delay(500);
  // set up weather kit
  myweatherMeterKit.setADCResolutionBits(10);
  myweatherMeterKit.begin();

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

// all the action happens when the interrupt timer (Wc_timer) fires.

void loop()
{
 
  client.loop();

  if (goTime) {
    printWeather();
    goTime = false;
  }
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

//Print the weather variables to serial and report via MQTT
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

  client.publish("ha/wind/speed", String(wind_speed));  delay(500);
  client.publish("ha/wind/dir", String(wind_dir));      delay(500);
  client.publish("ha/rain/total", String(rain));
}
