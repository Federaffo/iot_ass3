#ifndef __BLUETOOTH_TASK__
#define __BLUETOOTH_TASK__

#include "Task.h"
#include "SoftwareSerial.h"
#include "GlobalVar.h"
#include "string.h"
#include "ArduinoJson.h"

class BluetoothTask : public Task{
    public:
        BluetoothTask(int rx,int tx){
          BTSerial= new SoftwareSerial(rx,tx);
          BTSerial->begin(19200);
          init(200);
        }   
        void init(long period){
            Task::init(period);
        }
        void tick();
        
    
    private:
        SoftwareSerial* BTSerial;
        StaticJsonDocument<200> doc;
        void BTread();
        void BTawaitAlarm();
        void BTmanualControl();
};

#endif
