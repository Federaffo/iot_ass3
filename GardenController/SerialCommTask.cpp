#include "SerialCommTask.h"
#include "GlobalVar.h"

void SerialCommTask::tick(){
        ReadData();
    if(globalState==AUTO){
    }
}

void SerialCommTask::ReadData(){
    if(Serial.available()>0){
      
      String  x = Serial.readStringUntil('-');
      deserializeJson(doc, x);
     
      l1 = doc["l1"];
      l2 = doc["l2"];
      l3 = doc["l3"];
      l4 = doc["l4"];
      globalState = doc["state"];
      irrigation = doc["i"];
      /*irrSpeed = doc["irrSpeed"];*/
    }
    
}
