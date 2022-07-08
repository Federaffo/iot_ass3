

#include <ESP8266WiFi.h>
//#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
//#include <ArduinoHttpClient.h>
#include "Led.h"
#include "potentiometer.h"
#include "config.h"





const char* ssid     = STASSID;
const char* password = STAPSK;

Potentiometer* p = new Potentiometer();
Led* l1 = new Led(2);

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(WiFi.localIP());

  delay(500);
}


void loop() {  // wait for WiFi connection


p->sync();
int temp = p->getValue();

l1->turnOn();
if(WiFi.status()== WL_CONNECTED){

    String altLink = "http://192.168.1.6:80/sensorState?";
    altLink.concat("tmp=");
    altLink.concat(temp);
    altLink.concat("&lum=");
    altLink.concat(10);
    
    WiFiClient client;

    HTTPClient http;
    http.begin(client, altLink);
    //http.addHeader("Content-Type", "text/plain");
    int httpCode = http.GET();

    if (httpCode == 200){
      String response = http.getString();
      Serial.println(response);

      if( response == "ALARM"){
        l1->turnOff();
      }else{
        l1->turnOn();
      }
    }
    
    http.end();
    delay(5000);
  }
}
