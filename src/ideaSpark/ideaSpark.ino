/*********
  This code is tested to work with a commonly sold inexpensive weather station
  that lacks documentation (other than some useful images for wiring).  The
  station uses an ESP8266 NodeMCU 1.0 (ESP-12 module) such as sold by Adafruit. The
  kit includes the following sensors:
  - 0.96" 128x64 pixel min OLED display
  - DHT11 Temperature/Relative Humidity sensor
  - BMP180 Atmospheric Pressure sensor
  - GY-30 Light Intensity sensor
*********/

// wifi and mqtt 
#include "secrets.h"
#include <ESP8266WiFi.h> 
#include "Adafruit_MQTT.h"
#include "ADafruit_MQTT_Client.h"
#include "topics.h"
// timer
#include <Ticker.h>

#include <WiFiClientSecureBearSSL.h>

// Sensors
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BH1750.h>
#include <DHT.h>
#include <SFE_BMP180.h>
 
BH1750 lightMeter;
SFE_BMP180 pressure;
DHT dht(DHTPIN, DHTTYPE);
// SSD1306 display connected via I2C (SDA, SCL pins), see Wire.begin() in setup()
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Global vars
char status;
double T,P,p0,a;
float h = 0.0;
float t = 0.0; 
float l = 0.0;
double baseline; // For the pressure

int wifiTries = 0;
#define MAX_WIFI_RETRY 60 // we check every 500ms so this is 30s before giving up

// Set an interrupt timer to check and report data
Ticker weatherTicker; // Create a Ticker object
volatile bool goTime = false; // Use volatile for variables that can be changed in an interrupt
long weatherCheckFreq = 30000; // interval to check and report (in milliseconds)

// interrupt handler
void onNudge() {
  goTime = true;                    // minimal footprint here while we have everyone's attention
}

void setup(){
  Serial.begin(115200);
  delay(1500); // time to fiddle with serial window issues
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Connecting to WiFi");

  // Connect to WiFi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED && wifiTries < MAX_WIFI_RETRY) {
    wifiTries++;
    delay(500);
    Serial.print("."); 
  }
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi COULD NOT CONNECT");
    while (1) {
      digitalWrite(LED_BUILTIN, HIGH); delay(500);
      digitalWrite(LED_BUILTIN, LOW ); delay(500);
    }
  }

  // Connect to MQTT
  Serial.print("Connecting to MQTT... ");
  espClient->setInsecure();
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    Serial.println("Already connected!");
    return;
  }
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
      Serial.println(mqtt.connectErrorString(ret));
      Serial.println(mqtt.connectErrorString(ret)); // Print the error message
      Serial.println("Retrying MQTT connection in 5 seconds...");
      mqtt.disconnect();
      delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");

  // Initialize the sensors and OLED display
  //Wire.begin();       // if you used the default pins D1 for SCL and D2 for SDA
  Wire.begin(D3, D4);   // if you used D3 for SDA and D4 for SCL
  dht.begin();
  lightMeter.begin();
  lightMeter.configure(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
  if (!pressure.begin()){
    Serial.println("BMP180 init fail. Proceeding without it. Ignore pressure readings.\n\n");
    delay(2000);
  }
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Its works for my 128x64 OLED 0,96" screen
    Serial.println(F("SSD1306 allocation failed...proceeding without the OLED display"));
  }
  display.clearDisplay();
  display.setTextSize(1); //1-8; 1 is default, not needed
  display.setTextColor(WHITE); // Not relevant for one or two color OLED display but needed for the code
  display.setCursor(0,0); //0,0 to 120,57
  display.println("Welcome to ");
  display.println("WaggleWorld!!!!");
  display.display();
  delay(2000);
  display.clearDisplay();

  weatherTicker.attach_ms(weatherCheckFreq, onNudge); // start our timer for regular reporting

  Serial.println(F("Setup Complete"));     

}

void loop() {

  if (goTime) {
    MQTT_connect();
    readSensors();
    publishSensorData();
    displayValues();
    goTime = false;
  }


}
/* CeC: This is not very efficient but assumes each individual
        sensor has a unique code for sampling...
 */
void readSensors() {

  for (int i = 0; i < sizeof(sensorArray) / sizeof(sensorArray[0]); i++) {
    switch (sensorArray[i].sensorIndex){ 
      case 0:  
        sensorArray[i].sensorReading = dht.readTemperature();
        break;
      case 1:
        sensorArray[i].sensorReading = dht.readHumidity();
        break;
      case 2:
        status = pressure.startTemperature();
        delay(status);
        if (status != 0) {
            delay(status); // Wait for the measurement to complete:
            status = pressure.getTemperature(T);
            if (status != 0) {      
              status = pressure.startPressure(3);
              if (status != 0) {
              delay(status);
                status = pressure.getPressure(P,T);
                if (status != 0) {
                  p0 = pressure.sealevel(P,ALTITUDE); 
                }
              }
            }
        }
        sensorArray[i].sensorReading = p0;
        break;
      case 3: 
        sensorArray[i].sensorReading = lightMeter.readLightLevel();
        break;
    }
  } 
} 

/*  
  Display the sensor values on the OLED screen
  and serial out as well
 */
void displayValues() {
  String temp, humi, pres, lux;
  
  // Serial Print while building the display strings
    for (int i = 0; i < sizeof(sensorArray) / sizeof(sensorArray[0]); i++) {
      String payload = String(sensorArray[i].sensorReading, 2); // Convert float reading to String
      Serial.print(sensorArray[i].sensorVar);
      Serial.print(": ");
      Serial.println(payload.c_str());
      switch (sensorArray[i].sensorIndex) {
        case 0: // temperature
          temp = String(sensorArray[i].sensorReading,1);
          break;
        case 1: // RH
          humi = String(sensorArray[i].sensorReading,1);
          break;
        case 2: // presssure
          pres = String(sensorArray[i].sensorReading,1);
          break;
        case 3: // light
          lux = String(sensorArray[i].sensorReading,1);
          break;
      }
    }

  // Would be great if someone wants to dig in and improve the OLED display
  // code...which is borrowed from 

  // Calculate lux and pressure position according to its number length
  int pad1 = (lux.length() * 6) + 19;
  int pad2 = (pres.length() *6) + 19;

  // clear the display
  display.clearDisplay();
  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setCursor(85,0);
  display.print(temp);
  display.drawCircle(115, 1, 1, WHITE); // degree sign
  display.setCursor(118,0); // repositioning the Celsius display
  display.print("C");
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 12);
  display.print("Humidity:   ");
  display.setCursor(85,10);
  display.print(humi);
  display.print(" ");
  display.print("%"); 
  // display light data
  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("Illuminance: ");
  display.setCursor((SCREEN_WIDTH - pad1),20); 
  display.print(lux);
  display.print(" lx");
  // pressure
  display.setCursor(0,30);
  display.setTextSize(1);
  display.print("Pressure: ");
  display.setCursor((SCREEN_WIDTH - pad2),30); 
  display.print(pres);
  display.print(" P");
  display.display();
  //blink waiting for 5 seconds
  for (int k=0; k<5; k++){
    digitalWrite(LED_BUILTIN, HIGH); delay(750);
    digitalWrite(LED_BUILTIN, LOW ); delay(250);
  }
}
/* I don't like the inefficiency here but have not figured out how to get the feedname
    into the sensorConfig struct without jumping through hoops that risk memory mgmt
    issues with the Arduino/ESP runtime
 */
void publishSensorData() {

  for (int i = 0; i < sizeof(sensorArray) / sizeof(sensorArray[0]); i++) {
    String payload = String(sensorArray[i].sensorReading, 2); // Convert float reading to String
    switch (sensorArray[i].sensorIndex) {
      case 0:
        if (!tempFeed.publish(payload.c_str())) {        // feeds defined in topics.h
          Serial.println("tempFeed fail"); }
        break;
      case 1:
        if (!relhumFeed.publish(payload.c_str())) {
          Serial.println("relhumFeed fail"); }
        break;
      case 2:
        if (!atmpreFeed.publish(payload.c_str())) {
          Serial.println("atmprFeed fail"); }
        break;
      case 3:
        if (!lightFeed.publish(payload.c_str())) {
          Serial.println("lightFeed fail"); }
        break; 
    }
  }
}

/* MQTT code for AdaFruit 
    Function to connect and reconnect as necessary to the MQTT server.
    Should be called in the loop function and it will take care if connecting.
 */
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  int connectTries = 0;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println(mqtt.connectErrorString(ret)); // Print the error message
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(2500);  // wait 2.5 seconds
    if (connectTries++ > 10) {
       Serial.println("Giving up on MQTT...");
      while(1) { // Pause blinking fast forever.
        digitalWrite(LED_BUILTIN, HIGH); delay(250);
        digitalWrite(LED_BUILTIN, LOW ); delay(250);
      }
      return;
    }
  }
  Serial.println("MQTT Connected!");
}

