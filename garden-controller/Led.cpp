#include "Led.h"


Led::Led(int pin){
    this->pin=pin;
    state=OFF;
}

bool Led::isOn(){
    return this->state;
}

void Led::init(){
    pinMode(this->pin,OUTPUT);
}

void Led::turnOff(){
    if(state!=OFF){
        state=OFF;
        digitalWrite(pin, LOW);
    } 
}

void Led::turnOn(){
    if(state!=ON){
        state=ON;
        digitalWrite(pin, HIGH);
    }
}

void Led::dimmerLed(int i){
    analogWrite(this->pin,map(i,0,4,0,255));
}
