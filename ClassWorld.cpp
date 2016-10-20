#include "ClassWorld.hpp"

ClassWorld::ClassWorld()
{
  _counter_u8 = 0;
  _Rotary1_u8 = 0;
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

void ClassWorld::setRotary1(uint8_t value)
{
  _Rotary1_u8 = value;
}

uint8_t ClassWorld::getRotary1_u8()
{
  return _Rotary1_u8;
}

void ClassWorld::update()
{
  _counter_u8++;
}

void ClassWorld::updateFromBridge()
{
  const uint8_t stringSize=3;
  char bridgeValueStr[stringSize];

  
  // read rotary1:
  Bridge.get("rotary1",bridgeValueStr, stringSize);
  int rotary1 = atoi(bridgeValueStr);
  if( rotary1>=0 && rotary1<255 )
  {
    _Rotary1_u8=rotary1;
      /*
       Console.print("bridge value1  = ");
       Console.println(_Rotary1_u8);
       Console.print("bridge value2 = ");
       Console.println(getRotary1_u8());
      */
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