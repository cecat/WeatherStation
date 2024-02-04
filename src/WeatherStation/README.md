# SparkFun WeatherStation with MQTT for Home Assistant Integration

You should already have followed the instructions in the main README.md
for this repository to aseemble your SparkFun weather kit.  Here we will
set up the software environment and upload software to get your kit 
operations.


SparkFun weather station
([MicroMod Weather Carrier Board](https://www.sparkfun.com/products/16794)
with
[SparkFun MicroMod ESP32 processor](https://www.sparkfun.com/products/16781)
and
[Weather Meter Kit](https://www.sparkfun.com/products/15901).

## Set up your Computer with the Arduino IDE

Download and install the Arduino IDE app, which allows you to write and
upload software (*sketches*) to the processor in the weather kit.

* Macs: [https://www.arduino.cc/en/software](Download),
open, and move the app to your Applications folder.
* Windows: [Download](https://learn.sparkfun.com/tutorials/installing-arduino-ide#windows) and follow the directions at the download page.

## Set up Arduino IDE to upload to Carrier Board

In the Arduino IDE app you'll need to specify the processor you are using
(what we installed on the Carrier board) and the port (of your computer) that
is connected to the processor (i.e., via USB).

I am using the kit that has the **SparkFun ESP32 MicroMod** processor, so if you
have a different processor (there are multiple options) you'll need to slightly
tweak these instructions.

These instructions match the MacOS version, which is slightly different from
the PC version but should be straightforward to follow there.

### Set up the Arduino IDE board manager
In the Arduino IDE app, pull down the **Tools** menu to **Boards** and
slide right to select **Board Manager**. This will pull up a navigation
bar along the left side of the Arduino IDE app window with an
alphabetical list of items available to install. Scroll down to
**esp32 by Espressif Systems** and hit the green **INSTALL**  button.

### Add ESP32 boards library
Pull down to **Settings**. This will open a **Preferences** window.
At the bottom of that window where it says **Additional boards manager URLS:**
you need to paste in the URL below.  If there is already a URL in the window,
select the green button on the far right of the entry box for pasting.
**https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json**

### Plug stuff together
Now quit and reopen the Arduino IDE app, plug the Carrier Board into your
computer via USB.

### Set the Board 
Pull down **Tools** to **Board** and slide right to select **ESP32**,
then to the right again to select **SparkFun ESP32 MicroMod** (or, if you have
a different processor, select the one that matches yours)..

### Set the Port
Pull down the **Tools** menu again and select the option that begins
with **dev/cu.serial** (may be different on PC).

### Test
Finally, run a test program to make sure all of the above is set up and you
can upload software (*sketches*) to your board. In the Arduino IDE app,
pull down **File** to **Examples**, slide right to
**01. Basics** and then select **Blink**.  A new Arduino IDE window
will open with the sketch (code for the app to install on the carrier board).

Make sure the *board* and *port* are still configured. In the upper left
of the sketch window you should see a pull down with
**SparkFun ESP32 Micr…** (or the name of your processor, if different)
showing that your board and port are properly configured. If not,
then pull this menu down to **Select Other Board and Port** and use the
search bar in the resulting window to search for your processor
(in my case, **SparkFun ESP32 MicroMod**). Select it, then again select
the /dev/cu.usbserial… port.

In the Arduino IDE app window that now contains the **Blink** example sketch,
select the *check sign* icon in the upper left (left of the processor board
field).  The sketch should compile without any errors showing up in
a new “Output” section of the window that will appear below the code.

If you don't see errors, then compile and upload the sketch to the board.
To do this, select the *right-arrow* icon in upper left,
which will (again) compile the code and then upload to your carrier board.

If you have successfully completed all steps to this point you should see
the blue LED blinking on/off for 1s intervals.

## Set up and Run the Weather Station Code

Now that we are able to upload sketches to the carrier board we can install
the necessary libraries and software to make the Weather Station operational.

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
* ESP32MQTTClient by Patrick Lapointe

Quit/restart the Arduino IDE app just for good measure.

### Load the Weather Station Code

The file WeatherStaion.ino is the sketch that we need. Select it and you'll
see about 120 lines of code and just above the code is a menu bar. Off to the
right is a download icon to grab the code. Download the code and move it to
a folder on your machine where you'll keep your code, then open it from
the Arduino IDE. The IDE will tell you that
*"The file "WeatherStation.ino" needs to be inside a sketch
folder named "WeatherStation".  Create this folder, move the file,
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

## Acks

This code uses MQTT/WiFi to communicate with
[Home Assistant](https://www.home-assistant.io/). 

The code borrows from the
WiFi/MQTT library
[EspMQTTClient](https://github.com/plapointe6/EspMQTTClient)
by @plapointe6.

We also use code here from the *SparkFun Weather Station Carrier Board*
[example codes](https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/).

The timer functions were nicely documented in a short tutorial in
[Circuit Digest](https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts).

