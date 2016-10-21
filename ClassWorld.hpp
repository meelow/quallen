/*

*/
#ifndef ClassWorld_h
#define ClassWorld_h

#include "arduino.h"
#include <Bridge.h>

#define DEFAULT_LIGHT_u8 60

class ClassWorld
{
  public:
    ClassWorld();
    void setCounter(uint8_t c);
    uint8_t getCounter_u8();
    void update();
    void updateFromBridge();
    void setLight(uint8_t value);
    uint8_t getLight_u8();
    uint8_t XYpad1;
    uint8_t XYpad2;
  private:
    uint8_t _counter_u8;
    uint8_t _Light_u8;

};

#endif