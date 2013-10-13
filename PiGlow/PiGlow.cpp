/*
 *
 * This file is derived from wiringPi piGlow.c and modified for use with the PiGlow
 * on Arduino using the Wire library.
 *
 * The original piGlow.c file is part of wiringPi:
 *  https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 */
#include <Wire.h>
#include <Arduino.h>
#include "PiGlow.h"

 
/*
 * PiGlow.setup:
 *  Initialise the board
 *********************************************************************************
 */
 void PiGlow::setup(const int b = 255){

  brightness = b;

  Wire.begin();

  // Setup the chip
  this->piGlowCmd (0x00, 1) ;   // Not Shutdown
  this->piGlowCmd (0x13, 0x3F) ;  // Enable LEDs  0- 5
  this->piGlowCmd (0x14, 0x3F) ;  // Enable LEDs  6-11
  this->piGlowCmd (0x15, 0x3F) ;  // Enable LEDs 12-17
  this->piGlowCmd (0x16, 0x00) ;  // Update
  
};

/*
 * PiGlow.reset:
 *  Reset the board
 *********************************************************************************
 */
void PiGlow::reset(){
  this->piGlowCmd (0x17, 0) ;   // Reset
  this->piGlowCmd (0x00, 1) ;   // Not Shutdown
  this->piGlowCmd (0x13, 0x3F) ;  // Enable LEDs  0- 5
  this->piGlowCmd (0x14, 0x3F) ;  // Enable LEDs  6-11
  this->piGlowCmd (0x15, 0x3F) ;  // Enable LEDs 12-17
  this->piGlowCmd (0x16, 0x00) ;  // Update
};

/*
 * piGlowCmd:
 *  Send a single command to the PiGlow
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
 *  Light up a single LED on the piGlow
 *********************************************************************************
 */
void PiGlow::write (int pin, int value)
{
  int chan = 0x01 + (pin) ;
  
  if( this->brightness < 255 )
  {
    value = map(value, 0, 255, 0, this->brightness);
  }
  
  this->piGlowCmd (chan, value & 0xFF) ;  // Value
  this->piGlowCmd (0x16, 0x00) ;    // Update
};

void PiGlow::setBrightness( const int b ){
  this->brightness = b;
}

/*
 * piGlow1:
 *  Light up an individual LED
 *********************************************************************************
 */

void PiGlow::one (const int leg, const int ring, const int intensity)
{
  int *legLeds ;

  if ((leg  < 0) || (leg  > 2)) return ;
  if ((ring < 0) || (ring > 5)) return ;

  if (leg == 0)
    legLeds = leg0 ;
  else if (leg == 1)
    legLeds = leg1 ;
  else
    legLeds = leg2 ;

  this->write (legLeds [ring], intensity) ;
};

void PiGlow::hue(int h, int l)
{
  double s = 1, v = 1;
  //this is the algorithm to convert from RGB to HSV
  double r=0; 
  double g=0; 
  double b=0;

  double hf=h/60.0;

  int i=(int)floor(h/60.0);
  double f = h/60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s*f);
  double tv = v * (1 - s * (1 - f));

  switch (i)
  {
  case 0: //rojo dominante
    r = v;
    g = tv;
    b = pv;
    break;
  case 1: //verde
    r = qv;
    g = v;
    b = pv;
    break;
  case 2: 
    r = pv;
    g = v;
    b = tv;
    break;
  case 3: //azul
    r = pv;
    g = qv;
    b = v;
    break;
  case 4:
    r = tv;
    g = pv;
    b = v;
    break;
  case 5: //rojo
    r = v;
    g = pv;
    b = qv;
    break;
  }

  //set each component to a integer value between 0 and 255
  int red=constrain((int)255*r,0,255);
  int green=constrain((int)255*g,0,255);
  int blue=constrain((int)255*b,0,255);

  this->RGB(red,green,blue);
  this->ring(PIGLOW_RING_WHITE,l);
}

void PiGlow::RGB(int r, int g, int b)
{
  //r = map(r,0,255,0,120);
  this->ring(PIGLOW_RING_RED,r);
  this->ring(PIGLOW_RING_GREEN,g);
  this->ring(PIGLOW_RING_BLUE,b);
}

/*
 * piGlowLeg:
 *  Light up all 6 LEDs on a leg
 *********************************************************************************
 */

void PiGlow::leg (const int leg, const int intensity)
{
  int  i ;
  int *legLeds ;

  if ((leg < 0) || (leg > 2))
    return ;

  if (leg == 0)
    legLeds = this->leg0 ;
  else if (leg == 1)
    legLeds = this->leg1 ;
  else
    legLeds = this->leg2 ;

  for (i = 0 ; i < 6 ; ++i)
    this->write (legLeds [i], intensity) ;
};


/*
 * piGlowRing:
 *  Light up 3 LEDs in a ring. Ring 0 is the outermost, 5 the innermost
 *********************************************************************************
 */

void PiGlow::ring (const int ring, const int intensity)
{
  if ((ring < 0) || (ring > 5))
    return ;

  this->write (this->leg0 [ring], intensity) ;
  this->write (this->leg1 [ring], intensity) ;
  this->write (this->leg2 [ring], intensity) ;
};