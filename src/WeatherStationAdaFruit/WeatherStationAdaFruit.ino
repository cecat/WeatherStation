/*
  MQTT and WiFi functions here are adapted from the simple client
  example at EspMQTTClient by @plapointe6.
  (https://github.com/plapointe6/EspMQTTClient/tree/master)


  Weather Station functions are adapted from the SparkFun
  MM_WeatherMeter_Test example.
  (https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/tree/master)

  @cecat (12/29/23)

  @cecat (1/7/23)
	this is a complete overhaul implementing sensorArray with a 
	struct schema for each sensor.  For this version I have not
	figured out a clever way to embed the AdaFruit feed names
	into the struct or vice versa (spec them in the struct
	then config the feeds.  I have an idea to try out but for
	now wanted to get this version out so that at least we
	have something that works to get folks up and running.
  
*/

#include "secrets.h"
// for MQTT/WiFi Adafruit libraries
#include <WiFi.h>
#include "WiFiClientSecure.h"
#include "Adafruit_MQTT.h"
#include "ADafruit_MQTT_Client.h"
#include "SparkFun_Weather_Meter_Kit_Arduino_Library.h"  //http://librarymanager/All#SparkFun_Weather_Meter_Kit 
#include "topics.h"

// Create an instance of the weather meter kit
SFEWeatherMeterKit myweatherMeterKit(WDIR, WSPEED, RAIN);  


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

  //initialize Wifi and MQTT
  Serial.println(F("Adafruit IO MQTTS (SSL/TLS) Example"));
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  delay(500);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  delay(1000);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Set Adafruit IO's root CA
  client.setCACert(adafruitio_root_ca);

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
void onConnectionEstablished()
{
  Serial.println("connection good to go"); // this was where we originally were going to put the feed setup...moved to setup()
  
}

// all the action happens when the interrupt timer (Wc_timer) fires.
void loop()
{

  MQTT_connect();

  if (goTime) {
    //printWeather();
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
        case 3: // will mod the line below when I hook up the soil moisture sensor and it's prolly just an analogRead
          // sensorArray[i].sensorReading = static_cast<float>(readSoilMoistureSensor()); // Read int; convert to float
          break;
      }
    } 
}

void publishSensorData() {

    for (int i = 0; i < sizeof(sensorArray) / sizeof(sensorArray[0]); i++) {
        String topic = String(DEVICE_ID) + "/" + sensorArray[i].sensorName + "/" + sensorArray[i].sensorVar;
        String payload = String(sensorArray[i].sensorReading, 2); // Convert float reading to String
        switch (sensorArray[i].sensorIndex) {
          case 0:
            if (rainFeed.publish(payload.c_str())) {
              Serial.println(sensorArray[i].sensorVar);
              } else {  Serial.println("err"); }
            break;
          case 1:
            if (wind_dirFeed.publish(payload.c_str())) {
              Serial.println(sensorArray[i].sensorVar);
              } else {  Serial.println("err"); }
            break;
          case 2:
            if (wind_speedFeed.publish(payload.c_str())) {
              Serial.println(sensorArray[i].sensorVar);
              } else {  Serial.println("err"); }
           break;
           /*
          case 3:
            if (soilFeed.publish(payload.c_str())) {
              Serial.println("ok");
              } else {  Serial.println("err"); }
            break; 
            */
        }
    }
}
/*  Adafruit_MQTT_Publish rainFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/rain");
    Adafruit_MQTT_Publish wind_dirFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/wind_dir");
    Adafruit_MQTT_Publish wind_speedFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/wind_speed");
    Adafruit_MQTT_Publish soilFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/soil");
*/
/* MQTT code for AdaFruit */
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }

  Serial.println("MQTT Connected!");
}
