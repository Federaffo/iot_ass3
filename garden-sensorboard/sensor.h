#ifndef __SENSOR__
#define __SENSOR__

class Sensor
{
public:
    Sensor(int pin);
    int getValue();
    void sync();
    void init(int pin);
    int getMappedValue(int a,int b);

private:
    int pin;
    int value;
};

#endif
