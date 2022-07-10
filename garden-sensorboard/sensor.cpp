#include "sensor.h"
#include "Arduino.h"

Sensor::Sensor()
{
    this->value = 10;
    this->init();
}

int Sensor::getValue()
{
    return this->value;
}
void Sensor::sync()
{
    this->value  = analogRead(A0);
   
}

int Sensor::getMappedValue(int a, int b){
  return  map(this->value, 0, 1023, a, b);
}

void Sensor::init()
{
    pinMode(A0, INPUT);
}
