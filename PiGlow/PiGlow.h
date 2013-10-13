

#ifndef _PIGLOW_H
#define _PIGLOW_H 

#define	PIGLOW_ADDR	0x54

class PiGlow
{
 public:
PiGlow(){
  leg0 = {  6,  7,  8,  5,  4,  9 } ;
  leg1 = { 17, 16, 15, 13, 11, 10 } ;
  leg2 = {  0,  1,  2,  3, 14, 12 } ;
} 
  void piGlowSetup(int reset);
  void piGlowWrite (int pin, int value);
  void piGlow1 (const int leg, const int ring, const int intensity);
  void piGlowLeg (const int leg, const int intensity);
  void piGlowRing (const int ring, const int intensity);
 private:
  int leg0[6],leg1[6],leg2[6];
  void piGlowCmd( int reg, int data );
};

#endif
