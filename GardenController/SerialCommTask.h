#ifndef __SERIALCOMM_TASK__
#define __SERIALCOMM_TASK__

#include "Task.h"
#include "Arduino.h"
#include "wire.h"
#include "GlobalVar.h"
#include "string.h"
#include "ArduinoJson.h"

class SerialComm : public Task{
    public:
        SerialComm(){
            Serial.begin(9600);
        }

        void tick();
    
    private:
        GlobalState globalState;
        StaticJsonDocument<200> doc;
        bool l1;
        bool l2;
        int l3;
        int l4;
        bool irrigation;
        int irrSpeed;
        int state;

        void ReadData();
}

#endif