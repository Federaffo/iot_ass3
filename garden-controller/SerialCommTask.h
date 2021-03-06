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
          init(500);
        }
        void init(long period){
            Task::init(period);
        }

        void tick();
    
    private:
        StaticJsonDocument<200> doc;
        void WriteData();
        void ReadData();
        void AlarmMethod();
};

#endif
