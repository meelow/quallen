/*

*/
#ifndef SingleJellyFish_h
#define SingleJellyFish_h

#include "ClassWorld.hpp"
#include "FastLED.h"

class SingleJellyFish
{
  public:
    SingleJellyFish(uint8_t number, CRGBSet leds, ClassWorld &world);

    void paint();
  private:
    void paint_rainbow();
    void paint_palette();  
    void paint_confetti();
    void paint_bpm();

    CRGBSet _leds;
    uint8_t _counter_u8;
    const uint8_t _number_u8;
    ClassWorld &_world;
};

#endif