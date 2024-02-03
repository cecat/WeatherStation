# Sources

There are multiple versions of code here for two complementary weather
stations. The first is the 
SparkFun weather station
([MicroMod Weather Carrier Board](https://www.sparkfun.com/products/16794)
with
[SparkFun MicroMod ESP32 processor](https://www.sparkfun.com/products/16781)
and
[Weather Meter Kit](https://www.sparkfun.com/products/15901).

The second is a commonly used, poorly documented inexpensive kit that 
can be found online from a variety of vendors, with an attempt at
documentation (a few of the diagrams are useful) from a mysterious
entity called [ideaSpark](https://gitlab.com/GJKJ/WSK).

## SparkFun Weather Station

The **WeatherStation** source uses MQTT to communicate with Home Assistant.
The **WeatherStationAdaFruit** source uses MQTT to commuicate with AdaFruit.

## ideaSpark

The **ideaSpark** source uses MQTT to communicate with Home Assistant.
The **ideaSparkAdaFruit** source uses MQTT to communicate with AdaFruit.

# Getting Started

You'll need to do two things before moving on to installing software on your
weather kit(s).  You will need to
[assemble your kit](https://github.com/cecat/WeatherStation/tree/main/dev)
and you will need to
have the Arduino IDE app set up on your computer.

