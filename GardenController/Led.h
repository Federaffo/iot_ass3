#ifndef __LED__
#define __LED__

#include "string.h"
#include "Arduino.h"

class Led{
    public:
        Led(int pin);
        Led(unsigned char pin);
        bool isOn();
        void init();
        void turnOn();
        void turnOff();
        void dimmerLed(int i);
    
    private:
        int pin;
        unsigned char analPin;
        enum {OFF, ON, DIMMER} state;
};

#endif
