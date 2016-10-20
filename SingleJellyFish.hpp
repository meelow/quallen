/*

*/
#ifndef SingleJellyFish_h
#define SingleJellyFish_h

#include "ClassWorld.hpp"
#include "FastLED.h"

class SingleJellyFish
{
  public:
    SingleJellyFish(CRGBSet leds, ClassWorld &world);
    void paint_rainbow();
    void paint_palette();  
    void paint_confetti();
    void paint_bpm();
  private:
    CRGBSet _leds;
    uint8_t _counter_u8;
    ClassWorld &_world;
};

#endif