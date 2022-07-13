#include "sensor.h"
#include "Arduino.h"

Sensor::Sensor(int pin)
{
    this->pin = pin;
    this->init(pin);
}

int Sensor::getValue()
{
    return this->value;
}
void Sensor::sync()
{
    this->value  = analogRead(this->pin);
   
}

int Sensor::getMappedValue(int a, int b){
  return  map(this->value, 0, 4095, a, b);
}

void Sensor::init(int pin)
{
    pinMode(pin, INPUT);
}
