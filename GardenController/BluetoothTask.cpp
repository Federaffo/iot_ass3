#include "BluetoothTask.h"

void BluetoothTask::tick(){
    switch (globalState)
    {
    case MANUAL:
            BTread();
        break;
    case ALARM:
            BTread();
        break;
    default:
        break;
    }
    BTwrite();
}

void BluetoothTask::BTread(){
    if(BTSerial->available()){
      String comm=BTSerial->readString();
      BTSerial->print("dfasdfgs");
      deserializeJson(doc,comm);
      l1 = doc["l1"];
      l2 = doc["l2"];
      l3 = doc["l3"];
      l4 = doc["l4"];
      if(doc["state"]!=NULL){globalState = doc["state"];};
      irrigation = doc["irrigation"];
      /*irrSpeed = doc["irrSpeed"];*/
    }
}

void BluetoothTask::BTwrite(){
    ses["l1"]=l1;
    /*serializeJson("stocazzo" , *BTSerial);*/
    BTSerial->print("sus");
}
