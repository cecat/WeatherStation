# SparkFun WeatherStation with MQTT for AdaFruit MQTT Service

Here we will up the software for the SparkFun weather station
([MicroMod Weather Carrier Board](https://www.sparkfun.com/products/16794)
with
[SparkFun MicroMod ESP32 processor](https://www.sparkfun.com/products/16781)
and
[Weather Meter Kit](https://www.sparkfun.com/products/15901) to report
weather data to
[AdaFruit's free MQTT service](io.adafruit.com)..

You should already have followed the instructions in the 
[dev](https://github.com/cecat/WeatherStation/tree/main/dev) directory
to assemble your hardware, and the startup instructions in the 
[src](https://github.com/cecat/WeatherStation/tree/main/src) directory
to install drivers and the Arduino IDE on your computer.

## 1. Set up Arduino IDE to upload to Carrier Board

In the Arduino IDE app you'll need to specify the processor you are using
(what we installed on the Carrier board) and the port (of your computer) that
is connected to the processor (i.e., via USB).

I am using the kit that has the **SparkFun ESP32 MicroMod** processor, so if you
have a different processor (there are multiple options) you'll need to substitute
your processor as appropriate in these instructions.

These instructions match the MacOS version of the Arduino IDE,
where the menus are slightly different from
the PC version but should be straightforward to follow there.

### 1.1 Set up the Arduino IDE board manager
In the Arduino IDE app, pull down the **Tools** menu to **Boards** and
slide right to select **Board Manager**. This will pull up a navigation
bar along the left side of the Arduino IDE app window with an
alphabetical list of items available to install. Scroll down to
**esp32 by Espressif Systems** and hit the green **INSTALL**  button.

### 1.2 Add ESP32 boards library
Pull down to **Settings**. This will open a **Preferences** window.
At the bottom of that window where it says **Additional boards manager URLS:**
you need to paste in the URL below.  If there is already a URL in the window,
select the green button on the far right of the entry box for pasting and
add this URL as a line after the one(s) already there.
**https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json**

### 1.3 Plug the carrier board into your computer via USB
Now quit and reopen the Arduino IDE app, plug the Carrier Board into your
computer via USB.

### 1.4 Set the Board 
In the Arduio IDE, Pull down **Tools** to **Board** and slide
right to select **ESP32**. Slide right again from there and
select **SparkFun ESP32 MicroMod** (or, if you have
a different processor, select the one that matches yours).

### 1.5 Set the Port
Pull down the **Tools** menu again and select the option that begins
with **dev/cu.usbserial-nnnn** (where *nnnn* will vary between computers,
and may be different on PC).

### 1.6 Test
Finally, run a test program to make sure all of the above is set up and you
can upload software (*sketches*) to your board. In the Arduino IDE app,
pull down **File** to **Examples**, slide right to
**01. Basics** and then select **Blink**.  A new Arduino IDE window
will open with the sketch (code for the app to install on the carrier board).

Make sure the *board* and *port* are still configured. In the upper left
of the sketch window you should see a pull down with
**SparkFun ESP32 MicrMod** (possibly truncated depending on your window
width) or the name of your processor, if different)
showing that your board and port are properly configured. If not,
then pull this menu down to **Select Other Board and Port** and use the
search bar in the resulting window to search for your processor
(in my case, **SparkFun ESP32 MicroMod**). Select it, then again select
the **/dev/cu.usbserial-nnnn** port.

In the Arduino IDE app window that now contains the **Blink** example sketch,
select the *check sign* icon in the upper left (left of the processor board
field).  The sketch should compile without any errors showing up in
a new “Output” section of the window that will appear below the code.

If you don't see errors, then compile and upload the sketch to the board.
To do this, select the *right-arrow* icon in upper left of the sketch
window, which will compile the *Blink* sketch and then upload it
to your carrier board.

**If you have successfully completed all steps to this point you should see
the blue LED blinking on/off for 1s intervals.**

## 2. Set up and Run the Weather Station Code

Now that we are able to upload sketches to the carrier board we can install
the necessary libraries and software to make the Weather Station operational.

### 2.1 Install Libraries

We need to install some libraries for the weather station sensors.
In the Arduino IDE app, select **Tools -> Manage Libraries**.
This opens the Library Manager pane.

Use the search function in the Library Manager pane, to find
each of the following and then selecting the INSTALL button:

* SparkFun Weather Meter Kit Arduino
* [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library) (this will ask to also install Adafruit FONA, Adafruit SleepyDog, and WiFi101 (say 'install all'))

Quit/restart the Arduino IDE app just for good measure.

### 2.2 Load the Weather Station Code

The file **WeatherStaionAdaFruit.ino** is the sketch that we need. Select it and you'll
see about 120 lines of code (the sketch) and just above the
code is a menu bar. Off to the
right is a download icon. Download and move the file to
a folder on your machine where you'll keep your code, then open it from
the Arduino IDE. The Arduino IDE will tell you that
*"The file "WeatherStationAdaFruit.ino" needs to be inside a sketch
folder named "WeatherStationAdaFruit".  Create this folder, move the file,
and continue?"*
Select "OK" and let the IDE set it up for you.

### 2.3 Set up your local WiFi and MQTT secrets

Make a copy of the *secrets-template.h* file and name it *secrets.h*.
Edit it to substitute your WiFi SSID (name) and password in the 
placeholders for WLAN_SSID and WLAN_PASS..

Now you're going to need some information from a (free) account
you need to set up at
[io.adafruit.com](io.adafruit.com). Once you create the account there,
going to io.adafruit.com and logging in will land you at a dashboard.
From the dashboard page, click on the round yellow 
icon with a key in it on the upper right of the dashboard window
at [io.adafruit.com](io.adafruit.com).  There you will find some
API keys.  Copy the two #define lines in the Arduino code sample
window and paste them at the end of your secrets.h file
(deleting the placeholder lines).


### 2.4 Compile/Upload/Run the Sketch.

In the Arduion IDE, hit the right-arrow button (top left portion of the
sketch window) to compile and upload this sketch to your carrier board.
If everything above has been done correctly (and these instructions
are correct), an output pane will appear below
the sketch scrolling compile and upload progress 
and then reboots the carrier board to get the code running. 

Once the compile/upload is finished, open the Serial Monitor
pane by selecting the icon (looks like a magnifying glass) in the
upper right of the sketch window.

At this point, the Serial Monitor pane should now show a scrolling
set of reports with wind direction, speed, and rainfall.  If it shows
gibberish make sure that in the upper right of the Serial Monitor pane
it says 115200 baud.  If the baud rate is correctly set and you are
still seeing gibberish, try pressing the RESET button on the carrier board
or unplugging the USB cable then plugging back in.  Either of these
*should* get the serial window to display correctly.

## 4. Acks

This code uses MQTT/WiFi to communicate with
[Home Assistant](https://www.home-assistant.io/). 

The code borrows from the Adafruit MQTT library
[examples](https://github.com/adafruit/Adafruit_MQTT_Library/tree/master/examples/adafruitio_secure_esp32).

We also use code here from the *SparkFun Weather Station Carrier Board*
[example codes](https://github.com/sparkfun/MicroMod_Weather_Carrier_Board/).

The timer functions were nicely documented in a short tutorial in
[Circuit Digest](https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts).

