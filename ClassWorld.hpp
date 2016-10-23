/*

*/
#ifndef ClassWorld_h
#define ClassWorld_h

#include "arduino.h"
#include <Bridge.h>


#define DEFAULT_LIGHT_u8 60
#define DEFAULT_MODE1_u8 0
#define DEFAULT_MODE2_u8 0
#define DEFAULT_MODE3_u8 0
#define DEFAULT_PALETTE1_u8 0
#define DEFAULT_PALETTE2_u8 0
#define DEFAULT_PALETTE3_u8 0
#define DEFAULT_BPMFADE_TOGGLE 0 
#define DEFAULT_BPMFADE_VALUE 120 
#define DEFAULT_SEQUENTIAL_TOGGLE 0 
#define DEFAULT_SEQUENTIAL_VALUE 120 

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


    // should actually be privte:
    uint8_t _counter_u8;
    uint8_t _Light_u8;
    uint8_t _bing1_u8;
    uint8_t _bing2_u8;
    uint8_t _bing3_u8;
    uint8_t _BpmFadeToggle_u8;
    uint8_t _BpmFadeValue_u8;
    uint8_t _sequentialToggle_u8;
    uint8_t _sequentialValue_u8;
    uint8_t _mode1_u8;
    uint8_t _mode2_u8;
    uint8_t _mode3_u8;
    uint8_t _palette1_u8;
    uint8_t _palette2_u8;
    uint8_t _palette3_u8;  
  private:


};

#endif