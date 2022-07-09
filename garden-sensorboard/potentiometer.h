#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

class Potentiometer
{
public:
    Potentiometer();
    int getValue();
    void sync();
    void init();

private:
    int pin;
    int value;
};

#endif
