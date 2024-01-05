
#ifndef TOPICS_H
#define TOPICS_H

/* this really has evolved in to way more than topics, to include MQTT settings
   and sensor variables, along with topics...
   CeC (5-Jan-2024)
  */


// *********************** Sensors ************************** //

//Hardware pin definitions
const byte WSPEED = 14;     //Digital I/O pin for wind speed
const byte WDIR = 35;       //Analog pin for wind direction
const byte RAIN = 27;       //Digital I/O pin for rain fall

/*
    These fields allow us to construct the mqtt topic (to sub/pub)
    and also to loop through the sensors using the proper code for
    sampling (via sensorIndex) and grabbing the sensor's latest reading
    (sensorReading)l
 */
struct SensorConfig {
    int sensorIndex;      // arbitrary indexing to determine how to read;
                          // must put the proper sampling code in the switch statement
    String sensorName;    // sensor or package name (to look up datasheet)
    String sensorVar;     // sensor measurement name
    float sensorReading;  // latest reading from this sensor
  };
  
// Configuration for this device
#define DEVICE_ID "WMK"
  
SensorConfig sensorArray[] = {
    {0, "CN",     "rain",       0.0 },          
    {1, "CN",     "wind_dir",   0.0 },  
    {2, "CN",     "wind_speed", 0.0 },   
    {3, "AS3935", "soil",       0.0 }
};
/* Suggested for other sensors that we expect - move into the
   SensorConfig array list above, making sure to align the sensorIndex
   with the code/functions for sampling/reading and reporting

    {4, "AS3935",        "Lightning"},
    {5, "VEML075",       "UVA"},
    {6, "VEML075",       "UVB"},
    {7, "BME280",        "RelativeHumidity"},
    {8, "BME280",        "Temperature"},
    {9, "bME280",        "BarometricPressure"},

 */

const int sensorArraySize = sizeof(sensorArray) / sizeof(sensorArray[0]);

#endif
