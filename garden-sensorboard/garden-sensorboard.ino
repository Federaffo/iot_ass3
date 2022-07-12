

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include <ArduinoHttpClient.h>
#include "Led.h"
#include "sensor.h"
#include "config.h"
#include "Arduino.h"
#include <ArduinoJson.h>



const char* ssid     = STASSID;
const char* password = STAPSK;

Sensor* lux = new Sensor(A0);
Sensor* temp = new Sensor(A0);
Led* l1 = new Led(2);
WiFiClient client;

void SetupWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(9600);
  SetupWifi();
  delay(500);
}

void syncAll(){
  lux->sync();
  temp->sync();
}

void loop() {  // wait for WiFi connection

    int lum = lux->getMappedValue(0,8);
    int t = temp->getMappedValue(0,5);

  if(WiFi.status()== WL_CONNECTED){
    String altLink = "http://192.168.1.6:80/sensorState?";
    altLink.concat("tmp=");
    altLink.concat(5);
    altLink.concat("&lum=");
    altLink.concat(lum);
    

    HTTPClient http;
    http.begin(client, altLink);
    //http.addHeader("Content-Type", "text/plain");
    int httpCode = http.GET();

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
}
