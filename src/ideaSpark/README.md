# ideaSpark Weather Kit

This repository replaces the instruction manual for
the [ideaSpark Weather Station](https://gitlab.com/GJKJ/WSK).

You'll still want to download the Guide_Manual.. doc file
from the ideaSpark repo and unzip it as some of the figures are helpful
(though note that the Arduino IDE images are from Windows, where the
menus are slighly different than on a Mac).

The instructions here are tested only on a Mac.
using a MacBook with Apple silicon (M2).

If you have already set up the SparkFun Weather Station Kit
and gotten it running you'll already have done several of the steps
below.  You can skip step 2 in this case.

February 2024
CeCat

--------------------

## Step 1: Assemble the Kit

These kits require some soldering to put headers onto several of the 
sensors. Once you've done that, you're ready to assemble.  Note first 
that the ESP8266 processor board is too wide to straddle the middle
channel on the breadboards that came in the kit, but you only need the
pins on the right side (when viewing the board with the USB interface
facing down and toward you).  That is, the side with pins
D0, D1....G, 3V.

The image in the ideaSpark kit is helpful, though they are using pins
D3 and D4 to connect the OLED display and 2 of the sensors (using I2C).
The default for the I2C libraries is to use D1 and D2. It doesn't matter
which you use, as long as you select the right instance of **Wire.begin**
line within the *setup()* portion of the ideaSpark.ino code (about
line 62 or 63).

### Wiring

## Step 1: Install USB-To-Serial

### Download Drivers
Download the
[Mac OSX Driver](https://www.silabs.com/documents/public/software/Mac_OSX_VCP_Driver.zip).
from the Silicon Labs USB to UART Bridge VCP Drivers 
[download page](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads)).

Unzip the file and run the installer from the resulting folder. When you 
run the installer, you'll be asked if you want to open this file downloaded
from the Internet (yes), if you trust the source (yes), then
a popup will tell you that this installer is trying to modify
your system and do you want to cancel or **Open System Settings**.  
Select the latter and select the **Allow** button in the
*Privacy & Security* window that appears.

Repeat these steps to install the cH34 drivers, also a zip
file, from the
[ch34xser_macos git repository](https://github.com/WCHSoftGroup/ch34xser_macos).
 Here, there is a .dmg file that you can download (rather than going to the
linked site, which is not in English). Once unzipped, it will tell you
to drag the CH34xVCPDriver installer into your Applications folder.

Do that, open it,  and again when you receive the system blocked message
click to open *Privacy & Security* and *Allow* the software to load.

### Reboot

### Windows Notes
If you are a Windows PC user, there is a 
[video with a cheerful Windows tech guy](https://www.youtube.com/watch?v=4tKOnaz192E) 
who will walk you through checking to see if you need the driver, and finding and
installing the driver if you need it.*

## Step 2: Set up Arduino IDE

The original (Windows-specific) instructions say that one must use
Arduino IDE version 1.8.4.  That may be true on Windows but I am using
version 2.2.1 on a Mac and this works fine (if getting :"blink" to work
at the end of this step anyway).

### Add a source for board drivers 

At the bottom of the *Settings* (Arduino IDE -> Settings) window,
select the green icon to the right of the
*Additional boards manager URLs* text box.

Add a line to this window, pasting in:

**http://arduino.esp8266.com/stable/package_esp8266com_index.json**

### Install new boards drivers

After closing the *Settings* window, got to **Tools -> Board -> Boards Manager**
(if your Arduino IDE is already set up for another board, such as for the
[SparkFun WeatherStation](https://github.com/cecat/WeatherStation/tree/main/src/WeatherStationAdaFruit),
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

### Select the board

Now, go back to the 
*Tools -> Board* menu and select *-> ESP8266* then 
from the list of boards there select **NodeMCU 1.0 (ESP-12E Module)**.

### Set the Port 

In *Tools->Port*, select **dev/cu.usbserieal-####** where *####* is a
four-digit number.

### Test

At this point you can test to see if you can now load sketches onto
the ESP board from the Arduio IDE, so we will go to 
*File -> Examples -> Basics -> Blink* which will open a new sketch
window.  Here select the **->** button at the top left to upload
the sketch to your board.

You should see progress messages to compile then compress then write
the sketch to your board.  At the end of these messages it will 
tell you it's resetting the board and the LED should be blinking on/off
at 1s intervals.

It this is happening, well done we are ready to move on to install
the weather station sketch (code).

## Step 3

### Install the necessary Arduino libraries

In the Arduion IDE, go to Libraries and search for and install (with dependencies) the following
librarires:
* Adafruit GFX Library
* Adafruit SSD1306
* BH1750 (many search hits... I used "BH1750 by Christopher Laws")
* DHT sensor library (by Adafruit)

The final library needed, SFE_BMP180, will have to be installed manually.  

Navigate to 
[https://github.com/LowPowerLab/SFE_BMP180](https://github.com/LowPowerLab/SFE_BMP180) 
and download the library as a zip file.  To do this: toward the top, just left of "About"
is a "<> Code" button that yields a pull-down menu of options, including "Download Zip."

After downloading, in your Arduino IDE, Select from the top menubar "Sketch -> Include Zip Library"
and then navigate to your downloads folder and select the downloaded zip file (SFE_BMP180-master.zip).


### Download the weather code .ino in this folder.
(more detail to come)

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


