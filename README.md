# WeatherStation

SparkFun weather station
([MicroMod Weather Carrier Board](https://www.sparkfun.com/products/16794)
with 
[SparkFun MicroMod ESP32 processor](https://www.sparkfun.com/products/16781)
and 
[Weather Meter Kit](https://www.sparkfun.com/products/15901).

## Dependencies

The code here uses MQTT/WiFi to communicate with 
[Home Assistant](https://www.home-assistant.io/).

This code borrows heavily from the WiFi/MQTT library
[EspMQTTClient](https://github.com/plapointe6/EspMQTTClient)
by @plapointe6
and the SparkFun Weather Station Carrier Board 
[example codes](https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/). 
The timer functions were nicely documented in a short tutorial in
[Circuit Digest](https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts).

## To use this code

You can plug in your local specifics for WiFi and MQTT access if you
don't intend to share your code.  But it's better preactice to put
these into a separate file, *secrets.h*, placing this in the same
directory as the main code. There is a secrets-template.h that you can
use to enter your secrets.

The directory structure here has an extra layer below src because this is
what the Arduino IDE expects, so it allows you to use that app for managing
librarires, etc. 

From the Arduino IDE app you will need to use the library manager to
install the libraries for the weather station and each of its sensors,
in addition to the EspMQTTClient library (see the #includes in the code).

## About Home Assistant and the Broker used here...
I'm using a Home Assistant
[MQTT integration](https://www.home-assistant.io/integrations/mqtt/). 
The integration implements a broker and
you use MQTT topics (in the code, the *ha/wind/speed*, *ha/wind/dir*, etc. 
are topics) to match the payload of each topic to a variable you can use 
or display in HA.  Each device has a separate client name (i.e., the device
that is sending the data) so HA knows 
where the measurement is coming from).

HA integration is beyond the scope of this example but (using a different
MQTT client for Particle.io devices) you can see code and more detailed
instructions in my 
[UtilityWatchMQTT](https://github.com/cecat/UtilityWatchMQTT) repo..
