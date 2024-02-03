// secrets.h template - you must create a secrets.h from this template
// unless you prefer to keep your code local and unpublished, in which
// case you can live dangerously and just put these four #defines
// into your copy of WeatherStation.ino or topics.h,
// then remove the #include "secrets.h" line in WeatherStation.ino.
// (but you really should use secrets.h)

// wifi
#define WLAN_SSID     "your-wifi-ssid"
#define WLAN_PASS     "your-wifi-password""

// HA MQTT
const char *MQTT_USR    = "your-mqtt_usr_in_HA";
const char *MQTT_PWD    = "your-mqtt_pwd_in_HA";
const char *MQTT_CLIENT = "your-client_id_for_device";
char MQTT_BROKER[]        = "your-hostname";
//byte MQTT_BROKER[]      = { x, x, x, x }; // IP address

