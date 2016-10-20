#include <FastLED.h>
#include <Bridge.h>
#include "SingleJellyFish.hpp"
#include "ClassWorld.hpp"

#undef DEBUG
#ifdef DEBUG
  #include <Console.h>
#endif

#define NUM_LEDS 160


CRGBArray<NUM_LEDS> leds;
ClassWorld World;
SingleJellyFish jellyFish1( leds(0,    40), World );
SingleJellyFish jellyFish2( leds(50,   90), World );
SingleJellyFish jellyFish3( leds(100, 140), World );

void bootupAnimation()
{
  FastLED.setBrightness(128);
  for(uint8_t i=0; i<255; i++)
  {
   fill_rainbow( leds, NUM_LEDS, i, 1);
   FastLED.show();
  } 
}

void input()
{
  World.updateFromBridge();
}

void processing()
{
  World.update();
}

void output()
{
  jellyFish1.paint_confetti();
  jellyFish2.paint_palette();
  jellyFish3.paint_bpm();

  uint8_t bright = beatsin8( 60, 50, 150);
  FastLED.setBrightness( bright );
  
  FastLED.show();
}

void setup() 
{
  delay(3000); // 3 second delay for recovery

  // FastLED.addLeds<WS2812B>(leds, NUM_LEDS); 
  FastLED.addLeds<WS2812B,6,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); 

  bootupAnimation();
  
  Bridge.begin();
  #ifdef DEBUG
    Console.begin();
  #endif

  // make all leds black before starting to paint:
  leds.fill_solid(CRGB::Black);
}



void loop() 
{ 
  EVERY_N_MILLISECONDS(200) { input(); }
  EVERY_N_MILLISECONDS(29) { processing(); }
  EVERY_N_MILLISECONDS(30) { output(); }
  #ifdef asdf
    EVERY_N_MILLISECONDS(1000) 
    {
       Console.print("World.Rotary1=");
       Console.println(World.Rotary1);
    }
  #endif
}