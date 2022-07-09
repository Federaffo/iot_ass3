#include "StepMotor.h"
#include "Arduino.h"


StepMotor::StepMotor(int pin){
    this->pin=pin;
    degree=0;
}

void StepMotor::reset(){
    myServo.write(750);
}
void StepMotor::simulation(int g){
    myServo.write(map(g,0,180, 750, 2250));
}

void StepMotor::init(){
    myServo.attach(this->pin);
    this->reset();
}

void StepMotor::keepRotate(int speed){
    if(degree>=2250){
        degree-=10*speed;
    }else {
        degree+=10*speed;
    }
    simulation(degree);
}
