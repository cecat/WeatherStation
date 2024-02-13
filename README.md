# WeatherStation

This repository has code for two different weather stations:
* **SparkFun weather station** 
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
* **Generic ESP8266 weather kit for Arduino** sold by 
[multiple vendors](https://www.amazon.com/Mustpoint-Arduino-ESP8266-Weather-Tutorial/dp/B0BGHTD5M9/ref=sr_1_2?crid=30SF0VVSG1G7Q).  Some come with a QR code pointing to
a not-very-helpful manual but there is a 
[getting started guide](https://www.amazon.com/ESP8266-Weather-Station-Getting-Started-ebook/dp/B01LFX8Z5W/ref=sr_1_3?crid=CWIBWFT59Q82)
for one variant of this kit written by [Daniel Eichhorn](https://github.com/squix78)
that you can get for Kindle that is *very* good (see also his
[github repositories](https://github.com/squix78)). There is also a nice guide
from ThingPulse where they use the same kit (minus the BMP180) for
their 
[ESP8266 IoT Starter Kit](https://docs.thingpulse.com/guides/iot-starter-kit/).
There you'll also find a 
[downloadable PDF manual](https://blog.squix.org/weatherstation-guide)
if you want to explore the kit in more depth, similar to Eichhorn's book.

## Variants of Stations and Codes Here

There are two sets of sketches here (two for each of the stations).

### SparkFun Weather Kit
The Home Assistant (HA) variant uses MQTT/WiFi to communicate with 
[Home Assistant](https://www.home-assistant.io/). The other uses the
AdaFruit MQTT library that commuincates with the MQTT broker
service at [io.adafruit.com](https://io.adafruit.com/).

The HA variant also uses the WiFi/MQTT library
[EspMQTTClient](https://github.com/plapointe6/EspMQTTClient)
by @plapointe6.
The AdaFruit variant uses the
[AdaFruit_MQTT_Library](https://github.com/adafruit/Adafruit_MQTT_Library) 
and code borrowed from the *adafruitio_secure_esp32*
example code in that repository.

Both SparkFun sketches also borrow from the *SparkFun Weather Station Carrier Board* 
[example codes](https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/). 
The timer functions were nicely documented in a short tutorial in
[Circuit Digest](https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts).

### Generic ESP8266 Kit
Right now there is only code for the AdaFruit MQTT.  I have not yet modified for
HA.

# Getting Started

You'll need to do two things before moving on to installing software on your
weather kit(s).  You will need to 
* [assemble your kit](https://github.com/cecat/WeatherStation/tree/main/dev)
(the dev folder) and
* [set up the Arduino IDE](https://github.com/cecat/WeatherStation/tree/main/src)
app set up on your computer
(the src folder).

## Using these codes

Once you have completed the assembly and Arduino IDE set up you're ready to
Install the libraries and software you need.
Most of the libraries will be installed from within the Arduino IDE
app using the *library manager* to
install the libraries for the weather station, each of its sensors,
and the relevant MQTT libraries. The instructions for the code you 
are working with will walk you through.

In the **src** directory are implementations that work with
Home Assistant(HA) and AdaFruit's 
[free MQTT service](io.adafruit.com).

### Security and Credentials: secrets.h

All of these codes keep your credentials out of the main source
by using a secrets.h file.  You will need to create these for
each of your sketches.  Use the **secrets-template.h** files
to create your **secrets.h** file,
plugging in your local specifics for WiFi and MQTT access
There is a **secrets-template.h** for
each variant of the code as the MQTT specifics are different.

### Testing

For testing using the AdaFruit variants, you can see the message traffic 
at io.adafruit.com, which (when you log in) presents a dashboard.
For testing the HA variant you can monitor MQTT traffic from your
HA server by going to **Integrations->MQTT** and selecting
"**configure**."  There you can *listen* for specific topic streams.


## About Home Assistant and the MQTT Broker 
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

## Commentary
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
