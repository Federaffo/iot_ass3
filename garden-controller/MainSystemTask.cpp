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
    if(l1){L1->turnOn();}else{L1->turnOff();}
    if(l2){L2->turnOn();}else{L2->turnOff();}
    L3->dimmerLed(l3);
    L4->dimmerLed(l4);
    if(irrigation){motor->keepRotate(irrSpeed);}
    delay(100);
}

void MainSystemTask::AlarmMethod(){

}
