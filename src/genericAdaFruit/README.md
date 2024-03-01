# Generic ESP8266 Weather Kit

These instructions are for a generic ESP8266 weather kit for Arduino sold by
[multiple vendors](https://www.amazon.com/Mustpoint-Arduino-ESP8266-Weather-Tutorial/dp/B0BGHTD5M9/ref=sr_1_2?crid=30SF0VVSG1G7Q).  Some come with a QR code pointing to
a not-very-helpful manual from a group called 'ideaSpark' but there is a
[getting started guide](https://www.amazon.com/ESP8266-Weather-Station-Getting-Started-ebook/dp/B01LFX8Z5W/ref=sr_1_3?crid=CWIBWFT59Q82)
written by [Daniel Eichhorn](https://github.com/squix78)
that you can get for Kindle that is *very* good (see also his
[github repositories](https://github.com/squix78)).

The instructions here are tested only on a Mac.
using a MacBook with Apple silicon (M2).

At this point you should have already followed the instructions in the
[dev/ideaSpark](https://github.com/cecat/WeatherStation/tree/main/dev/ideaSpark)
directory to assemble your hardware, and the startup instructions in
the main 
[src](https://github.com/cecat/WeatherStation/tree/main/src)
directory to install drivers and the Arduino IDE on your computer.

## 1. Set up Arduino IDE to connect and upload to the ESP8266 processor

### 1.1 Add a source for board drivers 

In the Arduino IDE, select the main **Arduino IDE** menu and then
**Settings**. At the bottom of the *Settings* (Arduino IDE -> Settings) window,
select the green icon to the right of the
*Additional boards manager URLs* text box.

Add a line to this window (below any existing lines), pasting in:

"**http://arduino.esp8266.com/stable/package_esp8266com_index.json**"

### 1.2 Install new boards drivers

Close the *Settings* window and in the main menu bar select
**Tools -> Board -> Boards Manager**
(if your Arduino IDE is already set up for another board, such as for the
**SparkFun WeatherStation**,
the Boards Manager
item will have the name of that board...we are about to change it.)

This will open a menu bar to the left of your Sketch window.
In the search bar type **ESP8266** and you should see one result:
**ESP8266 by ESP8266 Community**.

Hit the green **INSTALL** button and you'll see an output window appear
at the bottom of your sketch window where you can watch the isntall
happen.  When it's finished, the **INSTALL** button will be replaced with
a **REMOVE** button which indicates the install completed (assuming you see
no errors to the contrary in the output window).

### 1.3 Select the board

Now, go back to the 
**Tools -> Board** menu and select **-> ESP8266** then 
from the list of boards there select **NodeMCU 1.0 (ESP-12E Module)**.

### 1.4 Set the Port 

In **Tools->Port**, select **dev/cu.usbserieal-nnnn** where *nnnn* is a
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
* [Adafruit MQTT Library]()  (this will ask to also add Adafruit FONA, Adafruit SleepyDog, and WiFi101 (say yes))
* [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) (this will ask to add Adafruit BusIO, Adafruit GFX (say yes))
* [BH1750](https://github.com/claws/BH1750)
* [Adafruit DHT](https://github.com/adafruit/DHT-sensor-library) (this will ask to add Adafruit Unified Sensor (say yes))


Navigate to 
[https://github.com/LowPowerLab/SFE_BMP180](https://github.com/LowPowerLab/SFE_BMP180) 
and download the library as a zip file.  To do this: toward the top,
just left of **About** is a **<> Code** button that yields a
pull-down menu of options, including **Download Zip**.

After downloading, in your Arduino IDE, Select from the
top menubar **Sketch -> Include Zip Library**
and then navigate to your downloads folder and select the
downloaded zip file (**SFE_BMP180-master.zip**).

Quit/restart the Arduino IDE app just for good measure.

## 3. Load the ideaSpark Weather Station Code

The file **ideaSpark.ino** is the sketch that we need. Select it and you'll
see about 180 lines of code (the sketch). Just above the
code is a menu bar, and off to the 
right is a **download icon**.
Download the .ino file and move it to
a folder on your machine where you keep your code. Now open it from
the Arduino IDE. The Arduino IDE will tell you that
*"The file "ideaSpark.ino" needs to be inside a sketch
folder named "ideaSpark".  Create this folder, move the file,
and continue?"*
Select "OK" and let the IDE set it up for you.

## 4 Set up your local WiFi and MQTT secrets

Make a copy of the *secrets-template.h* file and name it *secrets.h*.
Edit it to substitute your local specifics for WiFi and MQTT access into
the appropriate placeholders in the template.

### Home Assistant
For Home Assistant you'll find some instructions for MQTT setup
[here](https://github.com/cecat/UtilityWatchMQTT/tree/main/HASS).
There are also some tips on MQTT setup
[here](https://github.com/cecat/Lake-Watch).

### AdaFruit
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

## 5 Compile/Upload/Run the Sketch.

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
set of reports with temperature, atmospheric pressure, relative humidity,
and light intensity.  If it shows
gibberish and does not correct itself aftr a few seconds,
make sure that in the upper right of the Serial Monitor pane
it says 115200 baud.  If the baud rate is correctly set and you are
still seeing gibberish, try pressing the RESET button on the carrier board
or unplugging the USB cable then plugging back in.  Either of these
*should* get the serial window to display correctly.
