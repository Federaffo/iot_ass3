#include "Led.h"
#include "Arduino.h"

bool Led::isOn(){
    return this->state;
}

void Led::init(){
    pinMode(this->pin,OUTPUT);
}

void Led::turnOff(){
    if(state==ON){
        state=OFF;
        digitalWrite(pin,LOW);
    }
}

void Led::turnOn(){
    if(state==OFF){
        state=ON;
        digitalWrite(pin,HIGH);
    }
}
