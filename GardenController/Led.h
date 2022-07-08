#ifndef __LED__
#define __LED__



class Led{
    public:
        Led(int pin){
            this->pin=pin;
            state=OFF;
        }
        bool isOn();
        void init();
        void turnOn();
        void turnOff();
    
    private:
        int pin;
        enum {OFF,ON} state;
};

#endif