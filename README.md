# WeatherStation

SparkFun weather station
([MicroMod Weather Carrier Board](https://www.sparkfun.com/products/16794)
with 
[SparkFun MicroMod ESP32 processor](https://www.sparkfun.com/products/16781)
and 
[Weather Meter Kit](https://www.sparkfun.com/products/15901).

## Dependencies

There are two sketches here. One uses MQTT/WiFi to communicate with 
[Home Assistant](https://www.home-assistant.io/). The other uses the
AdaFruit MQTT library that commuincates with the MQTT broker
service at [io.adafruit.com](https://io.adafruit.com/).

The Home Assistant version of the code borrows heavily from the
WiFi/MQTT library
[EspMQTTClient](https://github.com/plapointe6/EspMQTTClient)
by @plapointe6.
The AdaFruit version takes code from the adafruitio_secure_esp32
example code in the
[AdaFruit_MQTT_Library](https://github.com/adafruit/Adafruit_MQTT_Library).

Both sketches use code from the *SparkFun Weather Station Carrier Board* 
[example codes](https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/). 
The timer functions were nicely documented in a short tutorial in
[Circuit Digest](https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts).

## To use this code

There are two versions of this code. One is using the EspMQTTClient to 
connect with Home Assistant; the other is using the AdaFruit MQTT 
library to connect with AdaFruit's MQTT service (io.adafruit.com).

You can plug in your local specifics for WiFi and MQTT access if you
don't intend to share your code.  But it's better preactice to put
these into a separate file, *secrets.h*, placing this in the same
directory as the main code. There is a secrets-template.h for
each version of the code that you can use to enter your secrets.

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
are topics) to match the payload of a MQTT message to a variable you can use 
or display in HA.  Each device also has a unique client name (i.e., the device
that is sending the data) so HA knows 
where the measurement is coming from.

HA integration is beyond the scope of this example but
you can see code and more detailed instructions in my 
[UtilityWatchMQTT](https://github.com/cecat/UtilityWatchMQTT) repo.
The code there is using a different MQTT client for Particle.io devices,
but there are some instructions on how to work the HA side of things that
does not care about what client library you are using.

For more general information on Home Assistant and how (and why)
I use it, see 
**A Primer on Home Assistant** in
[this blog](https://blog.deepblueberry.com/).
