#ifndef __BLUETOOTH_TASK__
#define __BLUETOOTH_TASK__

#include "Task.h"
#include "SoftwareSerial.h"
#include "GlobalVar.h"
#include "string.h"
#include "ArduinoJson.h"

class BluetoothTask : public Task{
    public:
        BluetoothTask(int rx, int tx){
            BTserial= SoftwareSerial(rx,tx);
            pinMode(rx,INPUT);
            pinMode(tx,OUTPUT);
            BTserial.begin(9600);
        }   

        void tick();
    
    private:
        SoftwareSerial BTserial;
        GlobalState globalState;
        StaticJsonDocument<200> doc;
        bool l1;
        bool l2;
        int l3;
        int l4;
        bool irrigation;
        int irrSpeed;
        int state;

        void BTread();
}

#endif