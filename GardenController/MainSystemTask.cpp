#include "MainSystemTask.h"

void MainSystemTask::tick(){
    
    switch (globalState)
    {
    case AUTO:
            doingStuff();
        break;
    
    case MANUAL:
            doingStuff();
        break;
    
    case ALARM:
            AlarmMethod();
        break;
    default:
        break;
    }
}

void MainSystemTask::doingStuff(){
    digitalWrite(13,HIGH);
    if(l1){L1->turnOn();}else{L1->turnOff();}
    if(l2){L2->turnOn();}else{L2->turnOff();}
    L3->dimmerLed(4);
    L4->dimmerLed(4);
    if(irrigation){motor->keepRotate(1);}
    delay(100);
    digitalWrite(13,LOW);
}

void MainSystemTask::AlarmMethod(){

}
