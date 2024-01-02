// Topics for the Waggle weather kit
//
// ---- THIS SCHEME NEEDS THOUGHT ---- 
//      (thus not implemented in the code yet)

/*
   Ideally AdaFruit would have unique device IDs but it seems that
   they allow you to define feeds (topics) even if you have not defined
   a device. That is, the "client" here is not the device but the
   username.  So this suggests we use something as a proxy for the
   device...

   "Device" - use Google Plus code for the location of the sensor
   (can get this from https://plus.codes/map and enter your location
   address). These have the form of XXXX+YY and I'm not sure if a "+"
   is allowed in an MQTT topic so I suggest changing to XXXX_YY.

   Sensor Package- E.g., BME280, VEML6075, AS3935, and for
   the Weather Meter Kit with rainfall, wind direction,
   wind speed, and soil moisture we will use "WMK".

   Sensor - e.g., for the BME280 we have temperature, pressure, and 
   relative humidity; for the WMK we have wind speed, etc.

*/

// Below one would fill out their Google Plus code for their
// location, substituting on each line for "G_PLUS"

const char *RAIN    =  "G_PLUS/WMK/RAIN"
const char *W_DIR   =  "G_PLUS/WMK/W_DIR"
const char *W_SPEED =  "G_PLUS/WMK/W_SPEED"
const char *SOIL    =  "G_PLUS/WMK/SOIL"
const char *LTNG    =  "G_PLUS/AS3935/SOIL"
const char *UVA     =  "G_PLUS/VEML075/UVA"
const char *UVB     =  "G_PLUS/VEML075/UVB"

chst char *RH       =  "G_PLUS/BME280/RH"
chst char *TEMP     =  "G_PLUS/BME280/TEMP"
chst char *BP       =  "G_PLUS/BME280/BP"
