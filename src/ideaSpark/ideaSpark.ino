/*********

  This code is tested to work with a commonly sold inexpensive weather station
  that lacks documentation (other than some useful images for wiring).  The
  station uses an ESP8266 NodeMCU 1.0 (ESP-12 module) such as sold by Adafruit. The
  kit includes the following sensors:
  - 0.96" 128x64 pixel min OLED display
  - DHT11 Temperature/Relative Humidity sensor
  - BMP180 Atmospheric Pressure sensor
  - GY-30 Light Intensity sensor

  Code for WiFi is lifted from 
  https://github.com/cecat/WeatherStation/tree/main/src/WeatherStationAdaFruit
  and with MQTT and timer approach from
  https://github.com/cecat/Lake-Watch
  while code for the sensor reading and display is from 
  https://github.com/Mategm
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BH1750.h>
#include <DHT.h>
#include <SFE_BMP180.h>
 
BH1750 lightMeter;
SFE_BMP180 pressure;
double baseline; // For the pressure

#define ALTITUDE 215.0 // Altitude of Naperville, IL (meters)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins) SDA = D2; SCL = D1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 14     // Digital pin connected to the DHT sensor as D5
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  delay(5000); // give time to clear serial window

  Serial.println(F("Initialize SSD"));          // DEBUG

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Its works for my 128x64 OLED 0,96" screen
    Serial.println(F("SSD1306 allocation failed"));
    while(1) { // Pause blinking forever.
      digitalWrite(LED_BUILTIN, HIGH); delay(500);
      digitalWrite(LED_BUILTIN, LOW ); delay(500);
    }
  }

  Serial.println(F("Clear display"));          // DEBUG

  display.clearDisplay();
  //Wire.begin();       // default pins D1 for SCL and D2 for SDA
  Wire.begin(D3, D4);   // if your wiring uses D3 for SDA and D4 for SCL
  dht.begin();
  
  lightMeter.begin();
  lightMeter.configure(BH1750::CONTINUOUS_HIGH_RES_MODE_2);

  display.setTextSize(1); //1-8; 1 is default, not needed
  display.setTextColor(WHITE); // Not relevant for one or two color OLED display but needed for the code
  display.setCursor(0,0); //0,0 to 120,57
  display.println("Weather Station by!");
  display.println("Mategm!");
  display.display();
  
  if (pressure.begin()){
    Serial.println("BMP180 init success");
    }
  else{
    Serial.println("BMP180 init fail\n\n");
    delay(5000);
    Serial.println("BMP180 init fail\n\n");

    while(1) { // Pause blinking forever.
      digitalWrite(LED_BUILTIN, HIGH); delay(250);
      digitalWrite(LED_BUILTIN, LOW ); delay(250);
    }
  }
  delay(2000);
  display.clearDisplay();

  Serial.println(F("Setup Complete"));          // DEBUG

}
void loop() {
  char status;
  double T,P,p0,a;
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature as Fahrenheit (isFahrenheit = true; default C as false)
  float l = lightMeter.readLightLevel();

  // pressure
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
          p0 = pressure.sealevel(P,ALTITUDE); // we're at 113 meters (Sarszentmiklos, Hungary)
        }
      }
    }
  }

   //Convert to string and cut de second decimal numbers
  String temp = String(t,1); 
  String humi = String(h,1);
  String lux  = String(l,1);
  String pres = String(p0,1);
  
  
  // Calculate lux and pressure position according to its number length
  int pad1 = (lux.length() * 6) + 19;
  int pad2 = (pres.length() *6) + 19;

  // clear the display
  display.clearDisplay();
  Serial.println

  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setCursor(85,0);
  display.print(temp);
  display.drawCircle(115, 1, 1, WHITE); // degree sign
  display.setCursor(118,0); // repositioning the Celsius display
  display.print("C");
  Serial.println("Temp: " + temp);
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.print("Humidity:   ");
  display.setCursor(85,10);
  display.print(humi);
  display.print(" ");
  display.print("%"); 
  Serial.println("RH  : " + humi + "%");


  // display light data
  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("Illuminance: ");
  display.setCursor((SCREEN_WIDTH - pad1),20); 
  display.print(lux);
  display.print(" lx");
  Serial.println("Lux : " + lux + "lx");

  // pressure
  display.setCursor(0,30);
  display.setTextSize(1);
  display.print("Pressure: ");
  display.setCursor((SCREEN_WIDTH - pad2),30); 
  display.print(pres);
  display.print(" P");
  Serial.println("BP  : " + pres);
 
  display.display();
  //delay(5000); // display the values for 5 seconds before update
  //blink for 5 seconds
  for (int k=0; k<5; k++){
    digitalWrite(LED_BUILTIN, HIGH); delay(750);
    digitalWrite(LED_BUILTIN, LOW ); delay(250);
  }
}
