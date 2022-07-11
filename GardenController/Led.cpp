#include "Led.h"


Led::Led(int pin){
    this->pin=pin;
    state=OFF;
}
 Led::Led(unsigned char pin){
    this->analPin=pin;
    state=OFF;
}

bool Led::isOn(){
    return this->state;
}

void Led::init(){
    if(pin==NULL){
        pinMode(this->analPin,OUTPUT);
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
