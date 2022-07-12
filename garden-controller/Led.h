#ifndef __LED__
#define __LED__

#include "string.h"
#include "Arduino.h"

class Led{
    public:
        Led(int pin);
        bool isOn();
        void init();
        void turnOn();
        void turnOff();
        void dimmerLed(int i);
    
    private:
        int pin;
        enum {OFF, ON, DIMMER} state;
};

#endif
