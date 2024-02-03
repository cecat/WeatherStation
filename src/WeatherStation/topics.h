
#ifndef TOPICS_H
#define TOPICS_H

/* this really has evolved to be less about topics (which we
   build dynamically and more about MQTT settings
   and sensor variables...
   CeC (5-Jan-2024)
  */

// *********************** MQTT Stuff *********************** //


// *********************** Sensors ************************** //

//Hardware pin definitions
const byte WSPEED = 14;     //Digital I/O pin for wind speed
const byte WDIR = 35;       //Analog pin for wind direction
const byte RAIN = 27;       //Digital I/O pin for rain fall

/*
    These fields allow us to construct the mqtt topic (to sub/pub)
    and also to loop through the sensors using the proper code for
    sampling (via sensorIndex) and grabbing the sensor's latest reading
    (sensorReading).

    sensorIndex is probably thinking too generally in that there might be
    more than one sensor that uses the same method for reading the value
    (perhaps if you had some simple analogRead sensors). I am still
    tempted to drop this field and just use the index in the switch
    statement...
 */
struct SensorConfig {
    int sensorIndex;      // arbitrary indexing to determine how to read;
                          // must put the proper sampling code in the
                          // switch statement in readSensors().
    String sensorName;    // sensor or package name (to look up datasheet)
    String sensorVar;     // sensor measurement name
    float sensorReading;  // latest reading from this sensor
  };
  
// Configuration for this device

// it would make sense in most cases to just use MQTT_CLIENT here...
// an easy change (2 references in WeatherStation.ino to change)
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
