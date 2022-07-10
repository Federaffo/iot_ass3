#ifndef __SENSOR__
#define __SENSOR__

class Sensor
{
public:
    Sensor();
    int getValue();
    void sync();
    void init();
    int getMappedValue(int a,int b);

private:
    int pin;
    int value;
};

#endif
