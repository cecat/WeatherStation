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
have the Arduino IDE app set up on your computer. We will do the latter here.

## Download and install the Arduino IDE app

* Macs: [https://www.arduino.cc/en/software](Download),
open, and move the app to your Applications folder.
* Windows: [Download](https://learn.sparkfun.com/tutorials/installing-arduino-ide#windows) and follow the directions at the download page.

## Set up Arduino IDE

In this repository are two different weather station components, each with its
own (different) Arduino-compatible processor.  

### Sparkfun Weather Meter Station Kit

I am using the kit that has the **SparkFun ESP32 MicroMod** processor, so if you
have a different processor (there are multiple options) you'll need to slightly
tweak these instructions.

These instructions match the MacOS version, which is slightly different from
the PC version but should be straightforward to follow there.

In the Arduino IDE app, [ull down the **Tools** menu to **Boards** and
slide right to select **Board Manager**. This will pull up a navigation
bar along the left side of the Arduino IDE app window with an
alphabetical list of items available to install. Scroll down to
**esp32 by Espressif Systems** and hit the green **INSTALL**  button.

Next, pull down to **Settings**. This will open a **Preferences** window.
At the bottom of that window where it says **Additional boards manager URLS:**
you need to paste in the URL below.  If there is already a URL in the window,
select the green button on the far right of the entry box for pasting.
**https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json**

Now quit and reopen the Arduino IDE app, plug the Carrier Board into your
computer via USB, and specify the board (processor) and port.  To do this,
pull down **Tools** to **Board** and slide right to select **ESP32**,
then to the right again to select **SparkFun ESP32 MicroMod** (or, if you have
a different processor, select the one that matches yours)..

Pull down the **Tools** menu again and select the option that begins
with **dev/cu.serial** (may be different on PC).

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

### ideaSpark Weather Kit

Follow the instructions
[here](https://github.com/cecat/WeatherStation/tree/main/src/ideaSpark).





