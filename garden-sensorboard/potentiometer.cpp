#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer()
{
    this->value = 10;
    this->init();
}

int Potentiometer::getValue()
{
    return this->value;
}
void Potentiometer::sync()
{
    int tmp = analogRead(A0);
    this->value = map(tmp, 0, 1023, 1, 5);
}

void Potentiometer::init()
{
    pinMode(A0, INPUT);
}
