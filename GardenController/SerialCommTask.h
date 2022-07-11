#ifndef __SERIALCOMM_TASK__
#define __SERIALCOMM_TASK__

#include "Task.h"
#include "Arduino.h"
#include "GlobalVar.h"
#include "string.h"
#include "ArduinoJson.h"

class SerialCommTask : public Task{
    public:
        SerialCommTask(){
          init(200);
        }
        void init(long period){
            Task::init(period);
        }

        void tick();
    
    private:
        StaticJsonDocument<200> doc;
        bool l1;
        bool l2;
        int l3;
        int l4;
        bool irrigation;
        int irrSpeed;
        int state;

        void ReadData();
};

#endif
