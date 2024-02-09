# Assembling the Generic ESP8266 Weather Kit

These kits require some soldering to put headers onto several of the
sensors. Once you've done that, you're ready to assemble.

Note first that the ESP8266 processor board is too wide
to straddle the middle channel on the breadboards that
came in the kit, but you only need the pins on the right
side (when viewing the board with the USB interface
facing down and toward you).  That is, the side with pins
D0, D1....G, 3V.

There are a few helpful guides for wiring this up. The wiring pin
assignments below will work with the code here. 

This code uses pins D3 and D4 for the I2C SCL/SCA connections.
While the default for the I2C libraries is to use D1 and D2 on
the ESP8266 I was unable to make this work via the default
Wire.begin() call nor explicitly specifying the pins in the
call (maybe I have a hardware issue...lmk if you make it work
with default pins!).  The downside of using
D4 is that this is also the LED_BUILTIN pin, so I'm not able
to do any clever signaling with the LED..

### Wiring things up

Below are wiring instructions that specify the endpoints for each 
jumper wire on your breadboard.  You'll notice that the ESP board
is supplying power and ground to all of the other devices, and that
one sensor (DHT11, temperature and relative humidity) connects
to its own pin but the other two sensors and the OLED display
are all connected to common pins (D1/D2 or D3/D4). These devices
use I2C, so they share an input channel (among other benefits, 
reducing the number of pins needed on the processor board).

In the image you'll see I am using a breadboard with power/ground
buses and this is handy to make wiring a bit easier to follow,
but the breadboard supplied in your kit works just fine too.

*Tip: Some of the guides I've seen use random colors for wiring,
making their images nearly impossible to follow.  It's *well worth it*
to use a color scheme to make debugging or changing the wiring on
your breadboard easier.  Choose one color for power (red), another
for ground (black), then the same colors for the pairs of wires
coming from the 3 I2C devices and a unique collor for the signal
wire coming from the DT11.  (the actual colors don't matter, just
the consistency)*

In the image below I'm using Black=GND, Orange=VCC,
Yellow=SDA, White=SCL, and Blue=OUT on the DHT11.

* OLED (display)
	* SCL <----> D4
	* SDA <----> D3
	* VCC <----> 3V
	* GND <----> G
* BH1750 (light intensity)
	* SCL <----> D4
	* SDA <----> D3
	* VCC <----> 3V
	* GND <----> G
* BMP180 (atmospheric pressure, temperature, relative humidity)
	* SCL <----> D4
	* SDA <----> D3
	* VCC <----> 3V
	* GND <----> G
* DHT11 (temperature, relative humidity)
	* OUT <----> D5
	* VCC <----> 3V
	* GND <----> G

Image of the wired-up breadboard::<br>
![wired breadboard](GenericESP8266wiring.jpeg)

