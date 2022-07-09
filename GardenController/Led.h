#ifndef __LED__
#define __LED__

#include "string.h"

class Led{
    public:
        Led(int pin){
            this->pin=pin;
            state=OFF;
        }
        Led(String pin){
            this.analPin;
            state=OFF;
        }
        bool isOn();
        void init();
        void turnOn();
        void turnOff();
        void dimmerLed(int i);
    
    private:
        int pin;
        String analPin;
        enum {OFF, ON, DIMMER} state;
};

#endif