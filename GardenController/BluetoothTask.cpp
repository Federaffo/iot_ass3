#include "BluetoothTask.h"

void BluetoothTask::tick(){

    /* sample JSON
    * { l1:false,
        l2:true,
        l3:3,
        l4:0,
        irrigation:true,
        irrSpeed:3,
        state:0}
    */
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
    deserializeJson(doc,BTserial);
    l1 = doc["l1"];
    l2 = doc["l2"];
    l3 = doc["l3"];
    l4 = doc["l4"];
    globalState = doc["state"];
    irrigation = doc["irrigation"];
    irrSpeed = doc["irrSpeed"];
}

