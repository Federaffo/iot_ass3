#include "StepMotor.h"
#include "Arduino.h"


StepMotor::StepMotor(int pin){
    this->pin=pin;
    s=10;
    degree=55;
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
    if(degree>=180){
        s=-s;
    }
    if(degree<=0){
        s=-s;
    }
    degree+=(s*speed);
    simulation(degree);
}
