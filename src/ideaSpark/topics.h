
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
                          // must put the proper sampling code in the switch statement
    String sensorName;    // sensor or package name (to look up datasheet)
    String sensorVar;     // sensor measurement name
    float sensorReading;  // latest reading from this sensor
  };

/************************* DEVICE CONFIG *********************/

/************************* Hardware **************************/
//Hardware pin assignments
const byte WSPEED = 14;     //Digital I/O pin for wind speed
const byte WDIR   = 35;     //Analog pin for wind direction
const byte RAIN   = 27;     //Digital I/O pin for rain fall

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
Adafruit_MQTT_Publish rainFeed = 
    Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.rain");
Adafruit_MQTT_Publish wind_dirFeed = 
    Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.winddir");
Adafruit_MQTT_Publish wind_speedFeed = 
    Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.windspeed");
Adafruit_MQTT_Publish soilFeed =  
    Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.soil");

/********************* SENSOR CONFIGURATION ********************************/

// Configuration for this device
SensorConfig sensorArray[] = {
    {0, "CN",     "rain",       0.0 },          
    {1, "CN",     "wind_dir",   0.0 },  
    {2, "CN",     "wind_speed", 0.0 },   
    {3, "AS3935", "soil",       0.0 }
};

/* Other sensors that we expect - move into the
   SensorConfig array list above, making sure to align the sensorIndex
   with the code/functions for sampling/reading and reporting.
   (also make sure to include their pin assigments above in 
   "*** Hardware ***")

    {4, "AS3935",  "Lightning",           0.0 },
    {5, "VEML075", "UVA",                 0.0 },
    {6, "VEML075", "UVB",                 0.0 },
    {7, "BME280",  "RelativeHumidity",    0.0 },
    {8, "BME280",  "Temperature",         0.0 },
    {9, "bME280",  "BarometricPressure",  0.0 },

 */

const int sensorArraySize = sizeof(sensorArray) / sizeof(sensorArray[0]);

#endif
