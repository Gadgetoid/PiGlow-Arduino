PiGlow For Arduino
==================

Installation
------------

Simple drop PiGlow into your Arduino libraries folder and load up the Demo Sketch.;

Usage
-----

    PiGlow piglow;

    void setup() {
    	piglow.setup(255); // Setup with brightness value
    	piglow.reset(); // Clear all LEDs

    	piglow.ring(0,255); // Light up the Red ring
    }

Connecting Up
-------------

The PiGlow takes two 3.3v inputs, one 5v input, one Ground and the I2C clock/data lines.


Orientate your PiGlow with the text facing and the right way up. Then flip to look at the back.

The pinout is as follows:

                            GND                      5v
                             |                       |
    [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]

    [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
                     |                       |   |   |
                    3.3v                    SCL SDA 3.3v
