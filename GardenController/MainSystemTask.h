#ifndef __MAINSYSTEM_TASK__
#define __MAINSYSTEM_TASK__

#include "Task.h"
#include "Led.h"
#include "StepMotor.h"
#include "GlobalVar.h"

class MainSystemTask : public Task{
    public:
        MainSystemTask(Led* L1, Led* L2, Led* L3, Led* L4,StepMotor* motor){
            this->L1=L1;
            this->L2=L2;
            this->L3=L3;
            this->L4=L4;
            this->motor=motor;
            init(200);
        }
        void init(long period){
            Task::init(period);
        }

        void tick();
    
    private:

        Led* L1;
        Led* L2;
        Led* L3;
        Led* L4;
        StepMotor* motor;


        void doingStuff();
        void ManualMethod();
        void AlarmMethod();

        

};

#endif
