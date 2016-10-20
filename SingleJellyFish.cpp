/*
  SingleJellyFish.cpp - Library for flashing SingleJellyFish code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "SingleJellyFish.hpp"


SingleJellyFish::SingleJellyFish(CRGBSet leds, ClassWorld &world)
:_leds(leds),
 _world( world )
{
}

void SingleJellyFish::paint_rainbow()
{
  _leds(0,_leds.size()).fill_rainbow(_world.getCounter_u8());
}

void SingleJellyFish::paint_palette()
{
  fill_palette (_leds, _leds.size(), _world.getCounter_u8(), 1, OceanColors_p, 250, LINEARBLEND);
}

void SingleJellyFish::paint_bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < _leds.size(); i++) { //9948
    _leds[i] = ColorFromPalette(palette, _world.getCounter_u8()+(i*2), beat-_world.getCounter_u8()+(i*10));
  }
}

void SingleJellyFish::paint_confetti()
{
  // The led strip is divided into a fixed number of compartments containing some LEDs. 
  // Randomly a compartment starts fading in and out again. Randomness controllable by gRotary1
  // Color of compartment can be choosen with xyPad1 and xyPad2
  uint8_t gRotary1=_world.getRotary1_u8();
  uint8_t gXYpad1=_world.XYpad1;
  uint8_t gXYpad2=_world.XYpad2;
  const uint8_t cCompartments=20;
  const uint8_t cCompartmentLength=_leds.size()/cCompartments;
  const uint8_t cFadeAmmount=10;
  static uint8_t lValueOfCompartment[cCompartments];
 
  // fade all existing compartments
  _leds.fadeToBlackBy( cFadeAmmount);
 
  // increase light in each compartmet until max, then switch off
  for( uint8_t currentCompartment=0; currentCompartment<cCompartments; currentCompartment++ )
  {
    if( lValueOfCompartment[currentCompartment] != 0 )
      lValueOfCompartment[currentCompartment]+=cFadeAmmount;
    if( lValueOfCompartment[currentCompartment] > 200 )
      lValueOfCompartment[currentCompartment] = 0;      
  }
  
  // paint the compartments
  for( uint8_t currentCompartment=0; currentCompartment<cCompartments; currentCompartment++ )
  {
    if( lValueOfCompartment[currentCompartment] != 0 )
    {
      for( uint8_t currentPixel=0; currentPixel<cCompartmentLength; currentPixel++)
      {
        uint8_t compartmentStartPixel = currentCompartment * cCompartmentLength;
        _leds[compartmentStartPixel+currentPixel] = CHSV( gXYpad1, gXYpad2, lValueOfCompartment[currentCompartment]);
      }
    }
  }

  // randomly select new compartments to 'grow' in light, but make sure at least 1 compartment is lit
  bool atLeastOneLit=false;
  for( uint8_t currentCompartment=0; currentCompartment<cCompartments; currentCompartment++ )
  {
    uint8_t compartmentMiddlePixel = (currentCompartment * cCompartmentLength) + cCompartmentLength/2;
    if( _leds[compartmentMiddlePixel] )
      atLeastOneLit=true;
  }      
  if( (atLeastOneLit==false) || (random8(255) < gRotary1) ) // shall we light one compartment?
  {
      uint8_t currentCompartment = random8(cCompartments);
      uint8_t middlePixelOfCompartment = (currentCompartment*cCompartmentLength)+cCompartmentLength/2;
      if( ! _leds[middlePixelOfCompartment] ) // make sure the compartment is not lit before
        lValueOfCompartment[currentCompartment] = 1;
  }

  EVERY_N_MILLISECONDS(1000) 
  {
     Console.print("World.Rotary1 = ");
     Console.println(_world.getRotary1_u8());
  }
}
