#include "ClassWorld.hpp"

ClassWorld::ClassWorld()
{
  _counter_u8 = 0;
  _Light_u8 = DEFAULT_LIGHT_u8;

}

void ClassWorld::setCounter(uint8_t c)
{
	_counter_u8 = c;
}

uint8_t ClassWorld::getCounter_u8()
{
  return _counter_u8;
}

void ClassWorld::setLight(uint8_t value)
{
  _Light_u8 = value;
}

uint8_t ClassWorld::getLight_u8()
{
  return _Light_u8;
}

void ClassWorld::update()
{
  _counter_u8++;
}

void ClassWorld::updateFromBridge()
{
  const uint8_t stringSize=3;
  char bridgeValueStr[stringSize];

  
  // read light:
  Bridge.get("light",bridgeValueStr, stringSize);
  int light = atoi(bridgeValueStr);
  if( light>=1 && light<=256 )
  {
    _Light_u8=light-1;
  } 
  else
  {
    _Light_u8=DEFAULT_LIGHT_u8;
  }    

  //////////////////////////////////////////////////////////////////////7777
  // read mode1 and palette1:
  Bridge.get("mode1",bridgeValueStr, stringSize);
  int mode1 = atoi(bridgeValueStr);
  if( mode1>0 && mode1<255 )
  {
    _mode1_u8 = mode1-1;
  } 
  else
  {
    _mode1_u8 = DEFAULT_MODE1_u8;
  }
  Bridge.get("palette1",bridgeValueStr, stringSize);
  int palette1 = atoi(bridgeValueStr);
  if( palette1>0 && palette1<255 )
  {
    _palette1_u8 = palette1-1;
  } 
  else
  {
    _palette1_u8 = DEFAULT_PALETTE1_u8;
  }
 


   //////////////////////////////////////////////////////////////////////7777
  // read mode2 and palette2:
  Bridge.get("mode2",bridgeValueStr, stringSize);
  int mode2 = atoi(bridgeValueStr);
  if( mode2>0 && mode2<255 )
  {
    _mode2_u8 = mode2-1;
  } 
  else
  {
    _mode2_u8 = DEFAULT_MODE2_u8;
  }
  Bridge.get("palette2",bridgeValueStr, stringSize);
  int palette2 = atoi(bridgeValueStr);
  if( palette2>0 && palette2<255 )
  {
    _palette2_u8 = palette2-1;
  } 
  else
  {
    _palette2_u8 = DEFAULT_PALETTE2_u8;
  }
 



   //////////////////////////////////////////////////////////////////////7777
  // read mode3 and palette3:
  Bridge.get("mode3",bridgeValueStr, stringSize);
  int mode3 = atoi(bridgeValueStr);
  if( mode3>0 && mode3<255 )
  {
    _mode3_u8 = mode3-1;
  } 
  else
  {
    _mode3_u8 = DEFAULT_MODE3_u8;
  }
  Bridge.get("palette3",bridgeValueStr, stringSize);
  int palette3 = atoi(bridgeValueStr);
  if( palette3>0 && palette3<255 )
  {
    _palette3_u8 = palette3-1;
  } 
  else
  {
    _palette3_u8 = DEFAULT_PALETTE3_u8;
  }
 


 ////////////////////////////////////////////
  // read BPMFade Value and toggle
  Bridge.get("bpmfade_toggle",bridgeValueStr, stringSize);
  int bpmfade_toggle = atoi(bridgeValueStr);
  if( bpmfade_toggle>0 && bpmfade_toggle<255 )
  {
    _BpmFadeToggle_u8 = bpmfade_toggle;
  } 
  else
  {
    _BpmFadeToggle_u8 = DEFAULT_BPMFADE_TOGGLE;
  } 

  Bridge.get("bpmfade_value",bridgeValueStr, stringSize);
  int bpmfade_value = atoi(bridgeValueStr);
  if( bpmfade_value>0 && bpmfade_value<255 )
  {
    _BpmFadeValue_u8 = bpmfade_value;
  } 
  else
  {
    _BpmFadeValue_u8 = DEFAULT_BPMFADE_VALUE;
  }



  ////////////////////////////////////////////
  // read sequential Value and toggle
  Bridge.get("sequential_toggle",bridgeValueStr, stringSize);
  int sequential_toggle = atoi(bridgeValueStr);
  if( sequential_toggle>0 && sequential_toggle<255 )
  {
    _sequentialToggle_u8 = sequential_toggle;
  } 
  else
  {
    _sequentialToggle_u8 = DEFAULT_SEQUENTIAL_TOGGLE;
  } 

  Bridge.get("sequential_value",bridgeValueStr, stringSize);
  int sequential_value = atoi(bridgeValueStr);
  if( sequential_value>0 && sequential_value<255 )
  {
    _sequentialValue_u8 = sequential_value;
  } 
  else
  {
    _sequentialValue_u8 = DEFAULT_SEQUENTIAL_VALUE;
  }


}
/*
void ClassWorld::print()
{
  #ifdef DEBUG
    Console.print("World.mode=");
    Console.println(_mode1_u8);

    Console.print("World._BpmFadeToggle_u8=");
    Console.println(_BpmFadeToggle_u8);
    Console.print("World._BpmFadeValue_u8=");
    Console.println(_BpmFadeValue_u8);


    Console.print("World._sequentialToggle_u8=");
    Console.println(_sequentialToggle_u8);
    Console.print("World._sequentialValue_u8=");
    Console.println(_sequentialValue_u8);
  #endif
}
*/