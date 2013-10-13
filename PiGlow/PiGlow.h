#ifndef _PIGLOW_H
#define _PIGLOW_H 

#define PIGLOW_RING_RED 0
#define PIGLOW_RING_YELLOW 1
#define PIGLOW_RING_ORANGE 2
#define PIGLOW_RING_GREEN 3
#define PIGLOW_RING_BLUE 4
#define PIGLOW_RING_WHITE 5
#define PIGLOW_ADDR 0x54

class PiGlow
{
 public:
PiGlow(){
  leg0 = {  6,  7,  8,  5,  4,  9 } ;
  leg1 = { 17, 16, 15, 13, 11, 10 } ;
  leg2 = {  0,  1,  2,  3, 14, 12 } ;
} 
  void setup(const int b);
  void write (int pin, int value);
  void one (const int leg, const int ring, const int intensity);
  void leg (const int leg, const int intensity);
  void ring (const int ring, const int intensity);
  void RGB ( const int r, const int g, const int b );
  void hue ( const int h, const int l = 0 );
  void setBrightness ( const int b );
  void reset();
  private:
  int leg0[6],leg1[6],leg2[6],brightness;
  void piGlowCmd( int reg, int data );
};

#endif