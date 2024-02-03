# SparkFun WeatherStation with MQTT for AdaFruit

You should already have followed the instructions in the main README.md
for this repository to aseemble your SparkFun weather kit, prepare
your carrier board, install the Arduino IDE on your computer, and
configure the Arduino IDE to work with your carrier board.

SparkFun weather station
([MicroMod Weather Carrier Board](https://www.sparkfun.com/products/16794)
with
[SparkFun MicroMod ESP32 processor](https://www.sparkfun.com/products/16781)
and
[Weather Meter Kit](https://www.sparkfun.com/products/15901).

## Dependencies

This code uses MQTT/WiFi to communicate with
[Home Assistant](https://www.home-assistant.io/). 

The code borrows from the
Adafruit MQTT library
[examples](https://github.com/adafruit/Adafruit_MQTT_Library/tree/master/examples/adafruitio_secure_esp32).

We also use code here from the *SparkFun Weather Station Carrier Board*
[example codes](https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/).

The timer functions were nicely documented in a short tutorial in
[Circuit Digest](https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts).

## Instructions

### Install Sensor Libraries

We need to install some libraries for the weather station sensors.
In the Arduino IDE app, select **Tools -> Manage Libraries**.
This opens the Library Manager pane.

Use the search function in the Library Manager pane, to find
each of the following and then selecting the INSTALL button.
In multiple cases you'll be asked if you also want to install
dependencies, and you want to always say yes to this:
* SparkFun BME
* SparkFun VEML6075
* SparkFun AS3935
* SparkFun Weather Meter Kit Arduino
* Adafruit MQTT Library

Quit/restart the Arduino IDE app just for good measure.

### Load the Weather Station Code

The file WeatherStaionAdaFruit.ino is the sketch that we need. Select it and you'll
see about 120 lines of code and just above the code is a menu bar. Off to the
right is a download icon to grab the code. Download the code and move it to
a folder on your machine where you'll keep your code, then open it from
the Arduino IDE. The IDE will tell you that
*"The file "WeatherStationAdaFruit.ino" needs to be inside a sketch
folder named "WeatherStationAdaFruit".  Create this folder, move the file,
and continue?"*
Here you can select "OK" and just let the IDE create that for you.

### Set up your local WiFi and MQTT secrets

Use the *secrets-template.h* files to create a *secrets.h* file,
plugging in your local specifics for WiFi and MQTT access. If you're
using Home Assistant you'll find some tips for MQTT setup 
[here](https://github.com/cecat/UtilityWatchMQTT/tree/main/HASS).
There are also some tips on MQTT setup 
[here](https://github.com/cecat/Lake-Watch).

### Compile/Upload/Run the Sketch.

In the Arduion IDE, hit the right-arrow button to compile and upload this
sketch to your carrier board. If everything above has been done correctly
(and these instructions are correct), the output pane will appear below
the sketch scrolling progress indicators as it checks (compiles) and
uploads the sketch, then resets the carrier board to get the code running. 

Open the Serial Monitor to see Sketch Output. Once it this is finished
uploading, open the Serial Monitor pane by selecting the icon in the
upper right of the sketch pane that looks like a magnifying glass.

At this point, the Serial Monitor pane should now show a scrolling
set of reports with wind direction, speed, and rainfall.  If it shows
gibberish make sure that in the upper right of the Serial Monitor pane
it says 115200 baud.  If the baud rate is correctly set and you are
still seeing gibberish, try pressing the RESET button on the carrier board
or unplugging the USB cable then plugging back in.  Either of these
*should* get the serial window to display correctly.

