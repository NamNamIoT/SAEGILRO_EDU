#include <WiFi.h>
#include "ModbusIP_ESP8266.h"
ModbusIP mb;

  
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("\r\nHello\r\n");
  
//  //Configure static IP
//  IPAddress local_IP(192, 168, 1, 123);
//  IPAddress gateway(192, 168, 1, 1);
//  IPAddress subnet(255, 255, 255, 0);
//  IPAddress primaryDNS(8, 8, 8, 8); //optional
//  IPAddress secondaryDNS(8, 8, 4, 4); //optional
//  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) { //Configure IP static
//    Serial.printf("\r\nConfigure statis IP fail");
//    }
//  else Serial.printf("\r\nConfigure statis IP success");

 WiFi.begin("NAME_WIFI", "PASS_WIFI");//Connect to wifi
 
  while (WiFi.status() != WL_CONNECTED) { //Loop until connect wifi success
    delay(500); //delay 500ms
    Serial.printf("\r\nWait..."); //print Wait...
  }
  
  Serial.printf("\r\nIP: ");
  Serial.println(WiFi.localIP());//Print IP
  mb.begin();
  mb.addHreg(1, 1);//Create register 1, Function code (FC) 03,  type Holding register (is meant 040001), value default is 1
  mb.addIreg(1, 1);//Create register 1, Function code (FC) 04,  type Input register (is meant 030001), value default is 1

  mb.addHreg(2, 0);//Create register 2, Function code (FC) 03,  type Holding register (is meant 040002), value default is 0
  mb.addIreg(2, 0);//Create register 2, Function code (FC) 04,  type Input register (is meant 030002), value default is 0

}
 
void loop() {
  
   mb.task();//Run task modbus TCP
   
   mb.Hreg(2, 1);//Write value 1 in to register 40002
   mb.Ireg(2, 3);//Write value 3 in to register 30002

   int value_1 = mb.Hreg(1); //Read value of register 40001
   int value_2 = mb.Ireg(1); //Read value of register 30001
   
   Serial.printf("\r\nValue of register 40001 is: %d", value_1); //print value of value_1
   Serial.printf("\r\nValue of register 30001 is: %d", value_2); //print value of value_2
   
   delay(500); //delay 500ms
}
