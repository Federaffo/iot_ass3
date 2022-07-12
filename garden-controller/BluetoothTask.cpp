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
}

void BluetoothTask::BTread(){
    if(BTSerial->available()){
      String comm=BTSerial->readString();
      
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
