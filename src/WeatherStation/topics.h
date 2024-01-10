
#ifndef TOPICS_H
#define TOPICS_H

/* this really has evolved to be less about topics (which we
   build dynamically and more about MQTT settings
   and sensor variables...
   CeC (5-Jan-2024)
  */

// *********************** MQTT Stuff *********************** //

// MQTT Stuff to unclutter the main code
// MQTT AdaFruit server
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 8883

// AdaFruit credentials
// Adafruit IO Account Configuration
// (to obtain these values, visit https://io.adafruit.com and click on Active Key)
//  AIO_USERNAME and AIO_KEY #defined in secrets.h

// String to hold our location identfier, which encodes lat/lon for use
// as the root part of our MQTT topics.

String LOCATION;

// Set up MQTT client for secure comms
WiFiClientSecure client;

// io.adafruit.com root CA
const char* adafruitio_root_ca = \
      "-----BEGIN CERTIFICATE-----\n"
      "MIIEjTCCA3WgAwIBAgIQDQd4KhM/xvmlcpbhMf/ReTANBgkqhkiG9w0BAQsFADBh\n"
      "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
      "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\n"
      "MjAeFw0xNzExMDIxMjIzMzdaFw0yNzExMDIxMjIzMzdaMGAxCzAJBgNVBAYTAlVT\n"
      "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
      "b20xHzAdBgNVBAMTFkdlb1RydXN0IFRMUyBSU0EgQ0EgRzEwggEiMA0GCSqGSIb3\n"
      "DQEBAQUAA4IBDwAwggEKAoIBAQC+F+jsvikKy/65LWEx/TMkCDIuWegh1Ngwvm4Q\n"
      "yISgP7oU5d79eoySG3vOhC3w/3jEMuipoH1fBtp7m0tTpsYbAhch4XA7rfuD6whU\n"
      "gajeErLVxoiWMPkC/DnUvbgi74BJmdBiuGHQSd7LwsuXpTEGG9fYXcbTVN5SATYq\n"
      "DfbexbYxTMwVJWoVb6lrBEgM3gBBqiiAiy800xu1Nq07JdCIQkBsNpFtZbIZhsDS\n"
      "fzlGWP4wEmBQ3O67c+ZXkFr2DcrXBEtHam80Gp2SNhou2U5U7UesDL/xgLK6/0d7\n"
      "6TnEVMSUVJkZ8VeZr+IUIlvoLrtjLbqugb0T3OYXW+CQU0kBAgMBAAGjggFAMIIB\n"
      "PDAdBgNVHQ4EFgQUlE/UXYvkpOKmgP792PkA76O+AlcwHwYDVR0jBBgwFoAUTiJU\n"
      "IBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQGCCsG\n"
      "AQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMDQGCCsGAQUFBwEB\n"
      "BCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQuY29tMEIGA1Ud\n"
      "HwQ7MDkwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEds\n"
      "b2JhbFJvb3RHMi5jcmwwPQYDVR0gBDYwNDAyBgRVHSAAMCowKAYIKwYBBQUHAgEW\n"
      "HGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9DUFMwDQYJKoZIhvcNAQELBQADggEB\n"
      "AIIcBDqC6cWpyGUSXAjjAcYwsK4iiGF7KweG97i1RJz1kwZhRoo6orU1JtBYnjzB\n"
      "c4+/sXmnHJk3mlPyL1xuIAt9sMeC7+vreRIF5wFBC0MCN5sbHwhNN1JzKbifNeP5\n"
      "ozpZdQFmkCo+neBiKR6HqIA+LMTMCMMuv2khGGuPHmtDze4GmEGZtYLyF8EQpa5Y\n"
      "jPuV6k2Cr/N3XxFpT3hRpt/3usU/Zb9wfKPtWpoznZ4/44c1p9rzFcZYrWkj3A+7\n"
      "TNBJE0GmP2fhXhP1D/XVfIW/h0yCJGEiV9Glm/uGOa3DXHlmbAcxSyCRraG+ZBkA\n"
      "7h4SeM6Y8l/7MBRpPCz6l8Y=\n"
      "-----END CERTIFICATE-----\n";


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
