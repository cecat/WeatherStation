/*
  MQTT and WiFi functions here are adapted from the simple client
  example at EspMQTTClient by @plapointe6.
  (https://github.com/plapointe6/EspMQTTClient/tree/master)

  Weather Station functions are adapted from the SparkFun
  MM_WeatherMeter_Test example.
  (https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/tree/master)

  @cecat (12/29/23)
  @cecat major overhaul implementing sensorArray (1/5/24)
  
*/

#include "secrets.h"
#include "EspMQTTClient.h"
#include "SparkFun_Weather_Meter_Kit_Arduino_Library.h"  //http://librarymanager/All#SparkFun_Weather_Meter_Kit 
#include "topics.h"

// Create an instance of the weather meter kit
SFEWeatherMeterKit myweatherMeterKit(WDIR, WSPEED, RAIN);  

// Create a WiFi/MQTT client
EspMQTTClient client(
  WIFI_SSID, WIFI_PWD,             // wifi ssid and password
  MQTT_BROKER, MQTT_USR, MQTT_PWD, // MQTT broker, username, password
  MQTT_CLIENT, 1883);		           // MQTT client name and port

// Set an interrupt timer to check and report weather data
bool goTime = false;                // set to true when timer fires; false after timer is serviced
int weatherCheckFreq = 30000000;    // interval to check and report (in microseconds)
hw_timer_t *Wc_timer = NULL;

// interrupt handler
void IRAM_ATTR onNudge() {
  goTime = true;                    // minimal footprint here while we have everyone's attention
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

void onConnectionEstablished() {

  // Set up and subscribe to topics for each sensor

  for (int i = 0; i < sizeof(sensorArray)/sizeof(sensorArray[0]); i++) {
      // Construct the MQTT topic for the current sensor
      String mqttTopic = String(DEVICE_ID) + "/" + sensorArray[i].sensorName + "/" + sensorArray[i].sensorVar;
      // Subscribe 
      client.subscribe(mqttTopic.c_str(), [](const String & payload) {
          Serial.println(payload);
      });
   }
}

// all the action happens when the interrupt timer (Wc_timer) fires.

void loop()
{
 
  client.loop();

  if (goTime) {
    readSensors();
    publishSensorData();
    goTime = false;
  }

}

void readSensors() {
    
  for (int i = 0; i < sizeof(sensorArray) / sizeof(sensorArray[0]); i++) {
    switch (sensorArray[i].sensorIndex){ 
      case 0:  
        sensorArray[i].sensorReading = myweatherMeterKit.getTotalRainfall();
        break;
      case 1:
        sensorArray[i].sensorReading = myweatherMeterKit.getWindDirection();
        break;
      case 2:
        sensorArray[i].sensorReading = myweatherMeterKit.getWindSpeed();
        break;
      case 3: // will mod the line below when I hook up the soil moisture sensor 
        // sensorArray[i].sensorReading = static_cast<float>(readSoilMoistureSensor()); // Read int; convert to float
        break;
    }
  } 
}

void publishSensorData() {

    for (int i = 0; i < sizeof(sensorArray) / sizeof(sensorArray[0]); i++) {
        String topic = String(DEVICE_ID) + "/" + sensorArray[i].sensorName + "/" + sensorArray[i].sensorVar;
        String payload = String(sensorArray[i].sensorReading, 2); // Convert float reading to String

        client.publish(topic.c_str(), payload.c_str());
    }
}
