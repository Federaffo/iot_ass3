

#include <ESP32WiFi.h>
//#include <ESP8266WiFiMulti.h>
#include <ESP32HTTPClient.h>
//#include <ArduinoHttpClient.h>
#include "Led.h"
#include "sensor.h"
#include "config.h"

#include <ArduinoJson.h>



const char* ssid     = STASSID;
const char* password = STAPSK;

Sensor* p = new Sensor();
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

     while (!Serial.available());
     String  x = Serial.readStringUntil('-');
    
    StaticJsonDocument<200> doc;
    String j = "{ \"l1\": False, \"l2\": False, \"l3\": 0, \"l4\": 0, \"irrigation\": False, \"state\": 0 }";
    x.replace("\\","");
    deserializeJson(doc, x);
    String altLink = "http://192.168.1.106:80/sensorState?";
    
    String a = doc["state"];
    String b = doc["l3"];
    altLink.concat(x);
    altLink.concat(a);
    altLink.concat(b);
    altLink.concat(j);
    altLink.concat(doc.isNull());


    
    WiFiClient client;

    HTTPClient http;
    http.begin(client, altLink);
    int httpCode = http.GET();
    if (httpCode == 200){
      String response = http.getString();
      Serial.println(response);
    }
  
    
    /*
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

    */
    
    http.end();
  }
}
