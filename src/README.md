# Getting Started

You'll need to do two things before moving on to installing software on your
weather kit(s).  You will need to
[assemble your kit](https://github.com/cecat/WeatherStation/tree/main/dev)
and you will need to
have the Arduino IDE app set up on your computer. 

Here we assume you have assembled your kits, and we will cover the installation
of the Arduino IDE and setting it up to communicate with your kit via USB.

Once you complete these steps you can select the kit and variant you are working
with and follow the kit- and variant-specific instructions in that directory.

## 1. Download and Install USB-To-Serial Driver

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

Repeat these steps to install the **CH34** drivers, also a zip
file, from the
[ch34xser_macos git repository](https://github.com/WCHSoftGroup/ch34xser_macos).
There you will find a .dmg file that you can download (rather than going to the
linked site, which is not in English).

Once unzipped, it will tell you
to drag the CH34xVCPDriver installer into your Applications folder.

Do that, open it,  and again when you receive the system blocked message
click to open *Privacy & Security* and *Allow* the software to load.

Reboot

*Windows Notes:
If you are a Windows PC user, there is a
[video with a cheerful Windows tech guy](https://www.youtube.com/watch?v=4tKOnaz192E)
who will walk you through checking to see if you need the driver, and finding and
installing the driver if you need it.*

## 2. Download and Install the Arduino IDE app

Download and install the Arduino IDE app, which allows you to write and
upload software (*sketches*) to the processor in the weather kit.

* Macs: [https://www.arduino.cc/en/software](Download),
open, and move the app to your Applications folder.
* Windows: [Download via SparkFun](https://learn.sparkfun.com/tutorials/installing-arduino-ide#windows) and follow the directions at the download page.

