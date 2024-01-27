# ideaSpark Weather Kit

This repository is intended to augment the instruction manual for
the [ideaSpark Weather Station](https://gitlab.com/GJKJ/WSK).

After downloading the instruction manual from the ideaSpark repo
and unzipping it, we will go through the manual here.

This is a work in progress to create instructions for Mac users. I'm
using a MacBook with Apple silicon (vs. Intel) and have not tested
with Intel silicon. I don't think the drivers are different, but I
have not tried with an Intel-based Mac.

January 2024

--------------------

## Step 1: Install USB-To-Serial

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
linked site, which is not in English. Once unzipped, it will tell you
to drag the CH34xVCPDriver installer into your Applications folder.

Do that, open it,  and again when you receive the system blocked message
click to open *Privacy & Security* and *Allow* the software to load.

Now **reboot** your Mac. 

## Step 2: Set up Arduino IDE

The original (Windows-specific) instructions say that one must use
Arduino IDE version 1.8.4.  That may be true on Windows but I am using
version 2.2.1 on a Mac and this works fine (if getting :"blink" to work
at the end of this step anyway).

### Add a new boards source and select the proper board

At the bottom of the *Settings* (Arduino IDE -> Settings) window,
select the green icon to the right of the
*Additional boards manager URLs* text box.

Add a line to this window, pasting in:

**http://arduino.esp8266.com/stable/package_esp8266com_index.json**

After closing this window, got to **Tools -> Board -> Boards Manager**
(if your system is already set up for another board, the Boards Manager
item will have the name of that board...we are about to change it.)

This will open a menu bar to the left of your Sketch window.
In the search bar type **ESP8266** and you should see one result:
*ESP8266 by ESP8266 Community.*

Hit the green **INSTALL** button and you'll see an output window appear
at the bottom of your sketch window where you can watch the isntall
happen.  When it's finished, the **INSTALL** button will be replaced with
a **REMOVE** button which indicates the install completed (assuming you see
no errors to the contrary in the output window).

Now, go back to the 
*Tools -> Board* menu and select *-> ESP8266* then 
from the list of boards there select **NodeMCU 1.0 (ESP-12E Module)**.

### Set the Port and Test

In *Tools->Port*, select **dev/cu.usbserieal-####** where *####* is a
four-digit number.

At this point you can test to see if you can now load sketches onto
the ESP board from the Arduio IDE, so we will go to 
*File -> Examples -> Basics -> Blink* which will open a new sketch
window.  Here select the **->** button at the top left to upload
the sketch to your board.

You should see progress messages to compile then compress then write
the sketch to your board.  At the end of these messages it will 
tell you it's resetting the board and the LED should be blinking on/off
at 1s intervals.

It this is happening, well done we are ready to move on.



## Step 3

## Step 4

## Step 5

## Step 6: Import WeatherStation code in the Arduino IDE


