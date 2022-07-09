#include "Led.h"
#include "Arduino.h"

bool Led::isOn(){
    return this->state;
}

void Led::init(){
    if(pin==null){
        pinMode(this->analPing,OUTPUT);
    }else{
        pinMode(this->pin,OUTPUT);
    }
}

void Led::turnOff(){
    if(state!=OFF){
        state=OFF;
        analogWrite(pin, LOW);
    } 
}

void Led::turnOn(){
    if(state!=ON){
        state=ON;
        analogWrite(pin, HIGH);
    }
}

void Led::dimmerLed(int i){
    analogWrite(pin,i);
    state=DIMMER;
}