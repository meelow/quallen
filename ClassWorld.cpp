#include "ClassWorld.hpp"

ClassWorld::ClassWorld()
{
  _counter_u8 = 0;
  _DEFAULT_LIGHT_u8 = 60;
  _Light_u8 = _DEFAULT_LIGHT_u8;
  XYpad1 = 0;
  XYpad2 = 0;
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
  if( light>=1 && light<255 )
  {
    _Light_u8=light;
  } 
  else
  {
    _Light_u8=_DEFAULT_LIGHT_u8;
  }    

  // read xypad:
  Bridge.get("xypad1",bridgeValueStr, stringSize);
  int xypad1 = atoi(bridgeValueStr);
  if( xypad1>0 && xypad1<255 )
  {
    XYpad1 = xypad1;
  } 
  Bridge.get("xypad2",bridgeValueStr, stringSize);
  int xypad2 = atoi(bridgeValueStr);
  if( xypad2>0 && xypad2<255 )
  {
    XYpad2 = xypad2;
  } 
 
}