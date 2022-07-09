#include "SerialCommTask.h"

void SerialCommTask::tick(){
    if(globalState==AUTO){
        ReadData();
    }
}

void SerialCommTask::ReadData(){
    deserializeJson(doc, Serial);
    l1 = doc["l1"];
    l2 = doc["l2"];
    l3 = doc["l3"];
    l4 = doc["l4"];
    globalState = doc["state"];
    irrigation = doc["irrigation"];
    irrSpeed = doc["irrSpeed"];
}