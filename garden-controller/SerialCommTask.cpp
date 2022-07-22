#include "SerialCommTask.h"
#include "GlobalVar.h"

void SerialCommTask::tick(){

  switch(globalState){
    case 0:
      ReadData();
      break;
    case 1:
      WriteData();
      break;
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

void SerialCommTask::WriteData(){
  StaticJsonDocument<200> sendJson;
  sendJson["state"]=globalState;
  sendJson["l1"]=l1;
  sendJson["l2"]=l2;
  sendJson["l3"]=l3;
  sendJson["l4"]=l4;
  sendJson["i"]=irrigation;
  sendJson["is"]=irrSpeed;
  serializeJson(sendJson, Serial);
  Serial.println();
}
