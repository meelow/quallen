#include <FastLED.h>
#include <Bridge.h>
#include "SingleJellyFish.hpp"
#include "ClassWorld.hpp"

#define DEBUG
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

  if( World._sequentialToggle_u8==1)
  {
    sequential();
  }
  else
  {
    jellyFish1.paint_confetti();
    jellyFish2.paint_palette();
    jellyFish3.paint_bpm();
  }

  if( World._BpmFadeToggle_u8==1 )
  {
    uint8_t bright = beatsin8( World._BpmFadeValue_u8, 0, World.getLight_u8());
    FastLED.setBrightness( bright );
  }
  else
    FastLED.setBrightness( World.getLight_u8() );
  
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
  EVERY_N_MILLISECONDS(100) { input(); }
  EVERY_N_MILLISECONDS(29) { processing(); }
  EVERY_N_MILLISECONDS(10) { output(); }

  #ifdef DEBUG
    EVERY_N_MILLISECONDS(1000) 
    {
/*
       Console.print("World.mode=");
       Console.println(World._mode1_u8);

       Console.print("World._BpmFadeToggle_u8=");
       Console.println(World._BpmFadeToggle_u8);
       Console.print("World._BpmFadeValue_u8=");
       Console.println(World._BpmFadeValue_u8);


       Console.print("World._sequentialToggle_u8=");
       Console.println(World._sequentialToggle_u8);
       Console.print("World._sequentialValue_u8=");
       Console.println(World._sequentialValue_u8);
       */
      World.print();
    }
  #endif
}


void sequential()
{
   // fade preveious colors (looks good when changing mode)
   const uint8_t cFadeAmmount=100;
   fadeToBlackBy( leds, NUM_LEDS, cFadeAmmount);
   
   uint8_t numberOfPixelsToBeat = beatsin8(World._sequentialValue_u8, 0, NUM_LEDS);

  for( uint8_t i=0; i<numberOfPixelsToBeat; i++ )
  {
    leds[i] = CRGB::Red;
  }

}