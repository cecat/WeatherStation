
#ifndef TOPICS_H
#define TOPICS_H

/* this really has evolved in to way more than topics, to include MQTT settings
   and sensor variables, along with topics...
   @cecat (5-Jan-2024)

   Some reorganization below, your device-specific changes will go down
   in the section beginning at "**** DEVICE CONFIG ****".  
   
   You'll also need to create your secrets.h file with local wifi name/password
   and other details for connecting via MQTT to Home Assistant. 
   
   @cecat (8-Jan-2024)

  */

// MQTT AdaFruit server
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 8883

/*  Going without security so yes, we might connect and give away our precious weather
    information to a site masqueriading as io.adafruit.com.  I gave up trying to make
    SSL certs work with the ESP8266 but others are welcome to give it a try!
 */
std::unique_ptr<BearSSL::WiFiClientSecure> espClient(new BearSSL::WiFiClientSecure());
Adafruit_MQTT_Client mqtt(espClient.get(), AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/******************* Config struct for configuration ********************/

/*  These fields allow (other MQTT implmentations) to construct the mqtt 
    topic (to sub/pub) and to loop through the sensors using the proper
    sampling code (via sensorIndex) and grabbing the sensor's latest reading
    (sensorReading) for publishing.

    sensorIndex: may be overly general anticipating the possibility 
    that multiple sensors might use the same method for reading the value
    (e.g., simple analogRead sensors or multiple instances of, say
    a soil moisture probe).

    sensorName and sensorVar: other than the Serial.print in 
    publishSensorData(), these are not used here with AdaFruit, but in
    other MQTT implementations we use them to dynamically
    create topics. One could remove them here (along with the
    Serial.print invocations in publishSensorData()) without any
    issues. But for now they at least help humans reading the code
    to follow which sensor is which

    sensorReading: given that AdaFruit wants a String as the payload (sensor reading)
    it might make sense to have sensorReading be a String here to avoid
    having to convert ints. This would just shift the conversion-to-String
    but does not avoid it, so it's probably 6 one way 3! the other.
 */
struct SensorConfig {
    int sensorIndex;      // arbitrary indexing to determine how to read;
                          // make sure to put the proper sampling code in the 
                          // readSensors() switch statement
    String sensorName;    // sensor or package name (to look up datasheet)
    String sensorVar;     // sensor measurement name
    float sensorReading;  // latest reading from this sensor
  };

/************************* DEVICE CONFIG *********************/

/************************* Hardware **************************/
#define ALTITUDE 215.0 // Altitude of Naperville, IL (meters)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// For I2C pin assignments see Wire.begin() in setup()
#define DHTPIN  14     // Digital pin connected to the DHT sensor as D5
#define DHTTYPE DHT11   // DHT 11


/************************** Feeds *****************************/
/*  I have tried multiple strategies to define these from our 
    sensorArray below and/or store them in the array, but to
    no avail. Absent that stratgegy we must manually align
    names/sensors/etc (maybe someone else can try?)
    THUS: The names (xxxFeed) and feeds ("/feeds/xxx") MUST align
          with the sensorArray list below and with the switch()
          statement in the function publishSensorData().
    AND: note that "waggletest" is the group name at io.adafruit.com
         for testing purposes. When you have things working, create a
         three-letter device name (e.g., your initials) and a
         corresponding GROUP at io.adafruit.com for your feeds, then
         replace "waggletest" with your group name.
 */
Adafruit_MQTT_Publish tempFeed = 
    Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.temp");
Adafruit_MQTT_Publish relhumFeed = 
    Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.relhum");
Adafruit_MQTT_Publish atmpreFeed = 
    Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.atmpre");
Adafruit_MQTT_Publish lightFeed =  
    Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.light");

/********************* SENSOR CONFIGURATION ********************************/

// Configuration for this device
SensorConfig sensorArray[] = {
    {0, "DHT11",     "temperature",     0.0 },          
    {1, "DHT11",     "rel_humidity",    0.0 },  
    {2, "BMP180",    "atm_pressure",    0.0 },   
    {3, "BH1750",    "light_intensity", 0.0 }
};

const int sensorArraySize = sizeof(sensorArray) / sizeof(sensorArray[0]);

#endif
