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

The Home Assistant version of the code borrows from the
WiFi/MQTT library
[EspMQTTClient](https://github.com/plapointe6/EspMQTTClient)
by @plapointe6.
The AdaFruit version borrows from the adafruitio_secure_esp32
example code in the
[AdaFruit_MQTT_Library](https://github.com/adafruit/Adafruit_MQTT_Library).

Both sketches also borrow from the *SparkFun Weather Station Carrier Board* 
[example codes](https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/). 
The timer functions were nicely documented in a short tutorial in
[Circuit Digest](https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts).

## To use this code

In the src directory is a WeatherStation implementation that works with
Home Assistant and a WeatherStationAdaFruit that
works with AdaFruit's MQTT service (io.adafruit.com).

Use the secrets-template.h files to create your secrets.h file,
plugging in your local specifics for WiFi and MQTT access
There is a secrets-template.h for
each version of the code as the MQTT specifics are different.

For testing, you can see the message traffic for the
AdaFruit version at io.adafruit.com
which (when you log in) will give you a dashboard.  For the
HA version you can go to Integrations->MQTT and select "configure,"
where you can listen for specific topic streams.

From the Arduino IDE app you will use the library manager to
install the libraries for the weather station and each of its sensors,
in addition to the EspMQTTClient or AdaFruit_MQTT_Library libraries
(see the #includes in the code).

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

## Comments
I'm not super happy with these implementations which require
hand-coding the mqtt topics for each sensor, but could not
find a way to dynamically build those given the limitations to
the Arduino/ESP implementations of C++ and tricky (fragile?) 
memory management features in those platforms. Would love it if
someone figured that out.

For more general information on Home Assistant and how (and why)
I use it, see 
**A Primer on Home Assistant** in
[this blog](https://blog.deepblueberry.com/).
