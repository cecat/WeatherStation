# WeatherStation

This repository has code for two different weather stations:
* SparkFun weather station
([MicroMod Weather Carrier Board](https://www.sparkfun.com/products/16794)
with 
[SparkFun MicroMod ESP32 processor](https://www.sparkfun.com/products/16781)
and 
[Weather Meter Kit](https://www.sparkfun.com/products/15901). 
The hardware assembly instructions from SparkFun are good, but embedded in
a lot of tutorial information. Similarly, the software tutorials and
documentation are very good. But in both cases the goal is to understand
how things work and how to program them, while this repo is intended to
be a quickstart for those who are more interested in the finished product
(measuring weather) than the technology.
* Generic ESP8266 weather kit for Arduino sold by 
[multiple vendors](https://www.amazon.com/Mustpoint-Arduino-ESP8266-Weather-Tutorial/dp/B0BGHTD5M9/ref=sr_1_2?crid=30SF0VVSG1G7Q).  Some come with a QR code pointing to
a not-very-helpful manual but there is a 
[getting started guide](https://www.amazon.com/ESP8266-Weather-Station-Getting-Started-ebook/dp/B01LFX8Z5W/ref=sr_1_3?crid=CWIBWFT59Q82)
written by [Daniel Eichhorn](https://github.com/squix78)
that you can get for Kindle that looks *very* good (as do his
[github repositories](https://github.com/squix78)).

In both cases above, it might be helpful to go through this quickstart
and then dive into the SparkFun tutorials and the Eichhorn Kindle book.
Or if your goal is to learn how to hack hardware and software then
by all means skip this and use those sources.

## Dependencies

There are two sets of sketches here (two for each of the stations).
One set uses MQTT/WiFi to communicate with 
[Home Assistant](https://www.home-assistant.io/). The other uses the
AdaFruit MQTT library that commuincates with the MQTT broker
service at [io.adafruit.com](https://io.adafruit.com/).

The Home Assistant version of the code uses the
WiFi/MQTT library
[EspMQTTClient](https://github.com/plapointe6/EspMQTTClient)
by @plapointe6.
The AdaFruit version uses the
[AdaFruit_MQTT_Library](https://github.com/adafruit/Adafruit_MQTT_Library) 
and code borrowed from the *adafruitio_secure_esp32*
example code in that repository.

Both SparkFun sketches also borrow from the *SparkFun Weather Station Carrier Board* 
[example codes](https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/). 
The timer functions were nicely documented in a short tutorial in
[Circuit Digest](https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts).

# Getting Started

You'll need to do two things before moving on to installing software on your
weather kit(s).  You will need to 
* [assemble your kit](https://github.com/cecat/WeatherStation/tree/main/dev)
(the dev folder) and
* [set up the Arduino IDE](https://github.com/cecat/WeatherStation/tree/main/src)
app set up on your computer
(the src folder).

## Using thse codes

Once you have completed the assembly and Arduino IDE set up you're ready to
Install the libraries and software you need.

In the src directory is a are implementations that work with
Home Assistant and AdaFruit 
(using AdaFruit's free 
[MQTT service](io.adafruit.com).

Use the secrets-template.h files to create your secrets.h file,
plugging in your local specifics for WiFi and MQTT access
There is a secrets-template.h for
each version of the code as the MQTT specifics are different.

For testing using the AdaFruit versions, you can see the message traffic for the
AdaFruit version at io.adafruit.com
which (when you log in) will give you a dashboard.  For testing the
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
I'm not super happy with the AdaFruit implementation, which requires
(afaict) hand-coding the mqtt topics for each sensor, but could not
find a way to dynamically build those (as in the implementation with
the EspMQTTClient library) given the limitations to
the Arduino/ESP implementations of C++ and tricky (fragile?) 
memory management features in those platforms. Would love it if
someone figured that out.

For more general information on Home Assistant and how (and why)
I use it, see 
**A Primer on Home Assistant** in
[this blog](https://blog.deepblueberry.com/).
