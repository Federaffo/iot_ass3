#include <WiFi.h>
#include <HTTPClient.h>
//#include <ArduinoHttpClient.h>
#include "Led.h"
#include "sensor.h"
#include "config.h"
#include "Arduino.h"
#include <ArduinoJson.h>



const char* ssid     = STASSID;
const char* password = STAPSK;

Sensor* lux = new Sensor(2);
Sensor* temp = new Sensor(1);
Led* l1 = new Led(3);
WiFiClient client;

void SetupWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(WiFi.localIP());
}


unsigned long lastTime = 0;
unsigned long timerDelay = 5000;


void setup() {
  Serial.begin(115200);
  SetupWifi();
  delay(500);
}

void syncAll(){
  lux->sync();
  temp->sync();
}

void loop() {  // wait for WiFi connection
  if ((millis() - lastTime) > timerDelay) {
    syncAll();
    int lum = lux->getMappedValue(1,8);
    int t = temp->getValue();
    t = map(t,0,470,1,5);
    

  if(WiFi.status()== WL_CONNECTED){
    String altLink = "http://192.168.1.106:80/sensorState?";
    altLink.concat("tmp=");
    altLink.concat(t);
    altLink.concat("&lum=");
    altLink.concat(lum);
    
    HTTPClient http;
    http.begin(client, altLink);
    //http.addHeader("Content-Type", "text/plain");
    int httpCode = http.GET();
    Serial.println(httpCode);

    if (httpCode == 200){
      String response = http.getString();
      Serial.println(response);

      if( response == "2"){
        l1->turnOff();
      }else{
        l1->turnOn();
      }
    }
    http.end();
  }
  
    lastTime = millis();
  }
}
