# ideaSpark Weather Kit

These instructions are for a generic ESP8266 weather kit for Arduino sold by
[multiple vendors](https://www.amazon.com/Mustpoint-Arduino-ESP8266-Weather-Tutorial/dp/B0BGHTD5M9/ref=sr_1_2?crid=30SF0VVSG1G7Q).  Some come with a QR code pointing to
a not-very-helpful manual but there is a
[getting started guide](https://www.amazon.com/ESP8266-Weather-Station-Getting-Started-ebook/dp/B01LFX8Z5W/ref=sr_1_3?crid=CWIBWFT59Q82)
written by [Daniel Eichhorn](https://github.com/squix78)
that you can get for Kindle that looks *very* good (as do his
[github repositories](https://github.com/squix78)).

The instructions here are tested only on a Mac.
using a MacBook with Apple silicon (M2).

If you have already followed the instructions in the
[dev/ideaSpark](https://github.com/cecat/WeatherStation/tree/main/dev/ideaSpark)
directory to assemble your hardware, and the startup instructions in
the main 
[src](https://github.com/cecat/WeatherStation/tree/main/src)
directory to isntall drivers and the Arduino IDE on your computer.

## 1. Set up Arduino IDE to connect and upload to the ESP8266 processor

### 1.1 Add a source for board drivers 

In the Arduino IDE, select the main **Arduino IDE** menu and then
**Settings**. At the bottom of the *Settings* (Arduino IDE -> Settings) window,
select the green icon to the right of the
*Additional boards manager URLs* text box.

Add a line to this window (below any existing lines), pasting in:

**http://arduino.esp8266.com/stable/package_esp8266com_index.json**

### 1.2 Install new boards drivers

Close the *Settings* window and in the main menu bar select
**Tools -> Board -> Boards Manager**
(if your Arduino IDE is already set up for another board, such as for the
**SparkFun WeatherStation**,
the Boards Manager
item will have the name of that board...we are about to change it.)

This will open a menu bar to the left of your Sketch window.
In the search bar type **ESP8266** and you should see one result:
*ESP8266 by ESP8266 Community.*

Hit the green **INSTALL** button and you'll see an output window appear
at the bottom of your sketch window where you can watch the isntall
happen.  When it's finished, the **INSTALL** button will be replaced with
a **REMOVE** button which indicates the install completed (assuming you see
no errors to the contrary in the output window).

### 1.3 Select the board

Now, go back to the 
*Tools -> Board* menu and select *-> ESP8266* then 
from the list of boards there select **NodeMCU 1.0 (ESP-12E Module)**.

### 1.4 Set the Port 

In *Tools->Port*, select **dev/cu.usbserieal-nnnn** where *nnnn* is a
four-digit number.

### 1.5 Test

At this point you can test to see if you can now load sketches onto
the ESP board from the Arduio IDE, so we will go to 
**File -> Examples -> Basics -> Blink** which will open a new sketch
window.  Here select the **->** button at the top left to upload
the sketch to your board.

You should see progress messages in the output pane below the code
in the sketch window as the sketch is compiled, compressed, and uploaded
to your board.   When finished, the messages will indicate that
the IDE is resetting the board and the LED should be blinking on/off
at 1s intervals.

It this is happening, well done we are ready to move on to install
the weather station sketch (code).

## 2. Install Libraries

In the Arduion IDE, go to Libraries and search for and install
(with dependencies) the following libraries:
* Adafruit GFX Library
* Adafruit SSD1306
* BH1750 (many search hits... use "BH1750 by Christopher Laws")
* DHT sensor library (by Adafruit)
* ESP32MQTTClient by Patrick Lapointe

The final library needed, SFE_BMP180, will have to be installed manually.  

Navigate to 
[https://github.com/LowPowerLab/SFE_BMP180](https://github.com/LowPowerLab/SFE_BMP180) 
and download the library as a zip file.  To do this: toward the top, just left of "About"
is a "<> Code" button that yields a pull-down menu of options, including "Download Zip."

After downloading, in your Arduino IDE, Select from the top menubar "Sketch -> Include Zip Library"
and then navigate to your downloads folder and select the downloaded zip file (SFE_BMP180-master.zip).


## Download the weather code .ino in this folder.

### Test

The code should now compile without errors.  You can check this without
the board installed using the Arduino IDE. In the sketch window there is
a 'check  mark' icon in hte upper left to just compile
the sketch.  This is just to the left of the 'right arrow' icon
which is to compile and upload to the board.

If you get any errors indicating that there is a missing xyz.h file
that means you did not get the right libraries, so must have missed
a step above (or that the instructions are incorrect).  Try searching
in the Libraries tab for the "xyz" part of the "xyz.h" in
the error message.


