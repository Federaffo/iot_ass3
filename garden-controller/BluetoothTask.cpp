#include "BluetoothTask.h"

void BluetoothTask::tick(){
    switch (globalState)
    {
      case AUTO:
            BTmanualControl();
          break;
      case MANUAL:
              BTread();
          break;
      case ALARM:
              BTawaitAlarm();
          break;
      default:
          break;
    }
}

void BluetoothTask::BTread(){
    if(BTSerial->available()){
      String comm=BTSerial->readString();
      deserializeJson(doc,comm);
      l1 = doc["l1"];
      l2 = doc["l2"];
      l3 = doc["l3"];
      l4 = doc["l4"];
      globalState = doc["state"];
      irrigation = doc["i"];
      irrSpeed = doc["is"];
    }
}

void BluetoothTask::BTmanualControl(){
  if(BTSerial->available()){
      char c = BTSerial->read();
      if(c=='m'){
        globalState=1;
        l1=false;
        l2=false;
        l3=0;
        l4=0;
        irrigation=false;
        irrSpeed=1;
        Serial.println("manualControl");
      }
    }
}

void BluetoothTask::BTawaitAlarm(){
  if(BTSerial->available()){
      char c = BTSerial->read();
      if(c=='a'){
        globalState=AUTO;
        l1=false;
        l2=false;
        l3=0;
        l4=0;
        irrigation=false;
        irrSpeed=1;
        Serial.println("exitAlarm");
      }
  }
}
