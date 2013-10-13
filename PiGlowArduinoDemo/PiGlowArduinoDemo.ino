#include <Wire.h>
#include "PiGlow.h"

#define PIGLOW_RING_RED 0
#define PIGLOW_RING_YELLOW 1
#define PIGLOW_RING_ORANGE 2
#define PIGLOW_RING_GREEN 3
#define PIGLOW_RING_BLUE 4
#define PIGLOW_RING_WHITE 5
#define BRIGHTNESS 50

int current_hue;

PiGlow piglow;

void setup() {
 current_hue = 0; 
 
 piglow.setup(BRIGHTNESS);
 piglow.reset(); // Clear previous state
 
 for(int x = 0;x<3;x++){
   for(int y = 0;y<255;y++){
    piglow.leg(x,y);
    delay(1); 
   }
   for(int y = 255;y>0;y--){
    piglow.leg(x,y);
    delay(1);
   }
 } 
 
 for(int z = 0;z<2;z++){
   for(int x = 0;x<6;x++){
     for(int y = 0;y<255;y++){
      piglow.ring(x,y);
      delay(1); 
     }
     for(int y = 255;y>0;y--){
      piglow.ring(x,y);
      delay(1);
     }
   }
 }
 
}

void loop() {
 piglow.hue(current_hue);
 current_hue++;
 if(current_hue >= 360) current_hue = 0;
  
 delay(10);
}
