/*
 *
 * This file is derived from wiringPi piGlow.c and modified for use with the PiGlow
 * on Arduino using the Wire library.
 *
 * The original piGlow.c file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 */
#include <Wire.h>
#include <Arduino.h>
#include "PiGlow.h"


 
/*
 * piGlow:
 *	Initialise the board
 *********************************************************************************
 */
 void PiGlow::piGlowSetup(int reset){

  Wire.begin();

  // Setup the chip
  if( reset ){
    this->piGlowCmd (0x17, 0) ;		// Reset
  }
  this->piGlowCmd (0x00, 1) ;		// Not Shutdown
  this->piGlowCmd (0x13, 0x3F) ;	// Enable LEDs  0- 5
  this->piGlowCmd (0x14, 0x3F) ;	// Enable LEDs  6-11
  this->piGlowCmd (0x15, 0x3F) ;	// Enable LEDs 12-17
  this->piGlowCmd (0x16, 0x00) ;	// Update
  

  /*if (reset)
  {
    // Initialise all 18 LEDs to off
    piGlowLeg (0, 0) ;
    piGlowLeg (1, 0) ;
    piGlowLeg (2, 0) ;
  }*/
}

/*
 * piGlowCmd:
 *	Send a single command to the PiGlow
 *********************************************************************************
 */
void PiGlow::piGlowCmd( int reg, int data )
{
  Wire.beginTransmission(PIGLOW_ADDR);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
};

/*
 * piGlowWrite:
 *	Light up a single LED on the piGlow
 *********************************************************************************
 */
void PiGlow::piGlowWrite (int pin, int value)
{
  int chan = 0x01 + (pin) ;
  
  this->piGlowCmd (chan, value & 0xFF) ;	// Value
  this->piGlowCmd (0x16, 0x00) ;		// Update
};

/*
 * piGlow1:
 *	Light up an individual LED
 *********************************************************************************
 */

void PiGlow::piGlow1 (const int leg, const int ring, const int intensity)
{
  int *legLeds ;

  if ((leg  < 0) || (leg  > 2)) return ;
  if ((ring < 0) || (ring > 5)) return ;

  /**/ if (leg == 0)
    legLeds = leg0 ;
  else if (leg == 1)
    legLeds = leg1 ;
  else
    legLeds = leg2 ;

  this->piGlowWrite (legLeds [ring], intensity) ;
};

/*
 * piGlowLeg:
 *	Light up all 6 LEDs on a leg
 *********************************************************************************
 */

void PiGlow::piGlowLeg (const int leg, const int intensity)
{
  int  i ;
  int *legLeds ;

  if ((leg < 0) || (leg > 2))
    return ;

  /**/ if (leg == 0)
    legLeds = leg0 ;
  else if (leg == 1)
    legLeds = leg1 ;
  else
    legLeds = leg2 ;

  for (i = 0 ; i < 6 ; ++i)
    this->piGlowWrite (legLeds [i], intensity) ;
};


/*
 * piGlowRing:
 *	Light up 3 LEDs in a ring. Ring 0 is the outermost, 5 the innermost
 *********************************************************************************
 */

void PiGlow::piGlowRing (const int ring, const int intensity)
{
  if ((ring < 0) || (ring > 5))
    return ;

  this->piGlowWrite (leg0 [ring], intensity) ;
  this->piGlowWrite (leg1 [ring], intensity) ;
  this->piGlowWrite (leg2 [ring], intensity) ;
};

