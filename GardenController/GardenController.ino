#include "Scheduler.h"
#include "Led.h"
#include "GlobalVar.h"
#include "StepMotor.h"
#include "MainSystemTask.h"
#include "SerialCommTask.h"
#include "BluetoothTask.h"


Led* L1= new Led(PINLED1);
Led* L1= new Led(PINLED2);
Led* L1= new Led(PINLED3);
Led* L1= new Led(PINLED4);
StepMotor* motor = new StepMotor(PINMOTOR);

Scheduler sched;
GlobalState globalState=AUTO;

void setup() {
  L1->init();
  L2->init();
  L3->init();
  L4->init();

  sched.init(50);

  Task* t0 = new MainSystemTask(L1,L2,L3,L4,motor);
  sched.addTask(t0);

  Task* t1 = new SerialCommTask();
  sched.addTask(t1);

  Task* t2 = new BluetoothTask(PIN_BT_RX, PIN_BT_TX);
  sched.addTask(t2);
}

void loop() {
  sched.schedule();
}
