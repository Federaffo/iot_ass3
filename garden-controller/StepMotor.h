#ifndef __STEPMOTOR__
#define __STEPMOTOR__

#include "ServoTimer2.h"
#include "Arduino.h"

 
class StepMotor { 
public:
  StepMotor(int pin);
  void simulation(int g);    
  void reset();
  void init();
  void keepRotate(int speed);
  
private:
  int pin;
  ServoTimer2 myServo;
  int degree;
  int s;
};

#endif
