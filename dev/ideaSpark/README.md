# Assembling the ideaSpark Kit

These kits require some soldering to put headers onto several of the
sensors. Once you've done that, you're ready to assemble.

Note first that the ESP8266 processor board is too wide
to straddle the middle channel on the breadboards that
came in the kit, but you only need the pins on the right
side (when viewing the board with the USB interface
facing down and toward you).  That is, the side with pins
D0, D1....G, 3V.

The image in the ideaSpark kit is helpful, though they are using pins
D3 and D4 to connect the OLED display and 2 of the sensors (using I2C).
The default for the I2C libraries is to use D1 and D2. It doesn't matter
which you use, as long as you select the right instance of **Wire.begin**
line within the *setup()* portion of the ideaSpark.ino code (about
line 62 or 63).

### Wiring things up

Below are wiring instructions that specify the endpoints for each 
jumper wire on your breadboard.  You'll notice that the ESP board
is supplying power and ground to all of the other devices, and that
one sensor (DHT11, temperature and relative humidity) connects
to its own pin but the other two sensors and the OLED display
are all connected to common pins (D1/D2 or D3/D4). These devices
use I2C, so they share an input channel (among other benefits, 
reducing the number of pins needed on the processor board).

*Tip: it's well worth it to use a color scheme to make debugging
your breadboard easier.  Choose one color for power (red), another
for ground (black), then the same colors for the pairs of wires
coming from the 3 I2C devices and a unique collor for the signal
wire coming from the DT11.  (the actual colors don't matter, just
the consistency)*

* OLED (display)
	* SCL <----> D1
	* SDA <----> D2
	* VCC <----> 3V
	* GND <----> G
* BH1750 (light intensity)
	* SCL <----> D1
	* SDA <----> D2
	* VCC <----> 3V
	* GND <----> G
* BMP180 (atmospheric pressure, temperature, relative humidity)
	* SCL <----> D1
	* SDA <----> D2
	* VCC <----> 3V
	* GND <----> G
* DHT11 (temperature, relative humidity)
	* OUT <----> D5
	* VCC <----> 3V
	* GND <----> G
