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
      digitalWrite(7,HIGH);
      delay(30000);
      jsonPY=x;
      x.replace("\\","");
      deserializeJson(doc, x);
      
      l1 = doc["l1"];
      if(l1==0){
      }
      Serial.println(x);
      l2 = doc["l2"];
      l3 = doc["l3"];
      l4 = doc["l4"];
      globalState = doc["state"];
      irrigation = doc["i"];
      /*irrSpeed = doc["irrSpeed"];*/
    }
    
}
