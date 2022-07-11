#include "Scheduler.h"
#include "Led.h"
#include "GlobalVar.h"
#include "StepMotor.h"
#include "MainSystemTask.h"
#include "SerialCommTask.h"
#include "BluetoothTask.h"
#include "Arduino.h"


Led* L1= new Led(PINLED1);
Led* L2= new Led(PINLED2);
Led* L3= new Led(PINLED3);
Led* L4= new Led(PINLED4);
StepMotor* motor = new StepMotor(PINMOTOR);

Scheduler sched;
GlobalState globalState=AUTO;
bool l1;
bool l2;
int l3;
int l4;
bool irrigation;
String jsonPY;

void setup() {
  L1->init();
  L2->init();
  L3->init();
  L4->init();
  sched.init(50);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  

  /*Task* t0 = new MainSystemTask(L1,L2,L3,L4,motor);
  sched.addTask(t0);*/

  Task* t2= new BluetoothTask(PIN_BT_RX, PIN_BT_TX);
  sched.addTask(t2);

  Task* t1 = new SerialCommTask();
  sched.addTask(t1);

  
}

void loop() {
  sched.schedule();
}
