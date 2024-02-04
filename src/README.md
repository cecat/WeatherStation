# Getting Started

You'll need to do two things before moving on to installing software on your
weather kit(s).  You will need to
[assemble your kit](https://github.com/cecat/WeatherStation/tree/main/dev)
and you will need to
have the Arduino IDE app set up on your computer. 

To keep the instructions all in one place, each of the src subdirectories
has all of the getting started materials you need after you assemble the 
hardware.

### Sparkfun Weather Meter Station Kit

I am using the kit that has the **SparkFun ESP32 MicroMod** processor, so if you
have a different processor (there are multiple options) you'll need to slightly
tweak the instructions.

The **WeatherStation** source uses MQTT to communicate with Home Assistant.
The **WeatherStationAdaFruit** source uses MQTT to commuicate with AdaFruit.

Instructions these are in their respective src folders as they
differ in terms of libraries needed and a few other specifics. 
The instructions match the
MacOS version, which is slightly different from
the PC version but should be straightforward to follow there.

### Generic (ideaSpark) ESP8266 Weather Kit

The **ideaSpark** source uses MQTT to communicate with Home Assistant.
The **ideaSparkAdaFruit** source uses MQTT to communicate with AdaFruit.

Instructions for these are in their respective src subdirectories.
