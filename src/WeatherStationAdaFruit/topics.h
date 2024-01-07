
#ifndef TOPICS_H
#define TOPICS_H

/* this really has evolved in to way more than topics, to include MQTT settings
   and sensor variables, along with topics...
   CeC (5-Jan-2024)
  */

// *********************** AdaFruit MQTT ******************** //

// MQTT AdaFruit server
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 8883

// WiFiFlientSecure for SSL/TLS support
WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

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


/****************************** Feeds ***************************************/

// Setup a feed called 'test' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>

//Adafruit_MQTT_Publish test = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/test");

// I tried to figure out a way to define these from our sensorArray below so we
// would not have to manually align names/sensors/etc but could not (maybe someone else can?)
// ******* NOTE: The names (xxxFeed) and feeds ("/feeds/xxx") MUST match the 
// *******       sensorArray list below and must also be manually inserted into the switch()
// *******       statement in the function publishSensorData().
Adafruit_MQTT_Publish rainFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.rain");
Adafruit_MQTT_Publish wind_dirFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.winddir");
Adafruit_MQTT_Publish wind_speedFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.windspeed");
Adafruit_MQTT_Publish soilFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waggletest.soil");


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
                          // must put the proper sampling code in the switch statement
    String sensorName;    // sensor or package name (to look up datasheet)
    String sensorVar;     // sensor measurement name
    float sensorReading;  // latest reading from this sensor
  };
  
// Configuration for this device

// Create your own 3-character ID such as your 3-letter initials

#define DEVICE_ID "CEC"   
  
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
