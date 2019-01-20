#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "esp.h"
#include "imu.h";


#include <iostream>
#include <string>

#pragma GCC diagnostic ignored "-Wwrite-strings"
//Our Wi-Fi ssdid and password
char* ssid = "ESP8266";
char* password = "Colloski8984";
ESP8266WebServer server; //server variable
 int thr,deg,str;
//Servo esc;
void setup() {
  //Making Connection With netword
  WiFi.begin(ssid, password);
  Serial.begin(9600);
  Serial.print("Searching Connection");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());
  serverSection();
  initial();
  initSetup();
}
int stabilized=0;
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void serverSection() {
  server.on("/", getSpeed);
  server.on("/status",getStatus);
  server.begin();
}

int state=0;
void getStatus(){
   String fstatus;
   fstatus=server.arg("status");
   state= fstatus.toInt();
  if(state == 0){
      initial();
      writeThrottle(0);
  }
  else if(state == 1){
    writeThrottle(0);
    detachPins();
  }
}
void  getSpeed() {
  String throttle,angle,strength,fstatus;
  throttle = server.arg("throttle");
  angle=server.arg("angle");
  strength=server.arg("strength");
  
  Serial.print("throttle");
  Serial.print('\t');
  thr = throttle.toInt();
  Serial.print(thr);
  writeThrottle(thr);
  Serial.print('\n');
  
  Serial.print("angle");
  Serial.print('\t');
  deg = angle.toInt();
  Serial.print(deg);
  Serial.print('\n');

  Serial.print("strength");
  Serial.print('\t');
  str = strength.toInt();
  Serial.print(str);
  Serial.print('\n');
  if(!(str==0 && deg==0)){
      stabilized=0;
      writeThrottle(init_rpms);
      setPath(deg,str);
  }
}
