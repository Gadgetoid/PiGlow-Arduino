#include <Wire.h>
#include <PiGlow.h>

#define RED 0
#define YELLOW 1
#define ORANGE 2
#define GREEN 3
#define BLUE 4
#define WHITE 5

#define BRIGHTNESS 255

int current_hue;
PiGlow piglow;

void setup() {
 Serial.begin(9600);
 Serial.println("hi");
 piglow.piGlowSetup(1);
 current_hue = 0; 
}

void loop() {
    Serial.println("hi");
    set_led_colour_hsv(current_hue,1,1);
    current_hue++;
    if(current_hue >= 360)
    {
      current_hue = 0;
    }
    delay(10);
}


void set_led_colour(int r, int g, int b)
{
  r = map(r,0,255,0,120);
 
  r = map(r, 0, 255, 0, BRIGHTNESS);
  g = map(g, 0, 255, 0, BRIGHTNESS);
  b = map(b, 0, 255, 0, BRIGHTNESS);
  
  piglow.piGlowRing(RED,r);
  piglow.piGlowRing(GREEN,g);
  piglow.piGlowRing(BLUE,b);
}

void set_led_colour_hsv(int h, double s, double v)
{
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

  set_led_colour(red,green,blue);
}

