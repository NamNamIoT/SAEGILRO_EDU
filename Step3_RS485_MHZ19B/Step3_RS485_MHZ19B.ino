#include "kitdevesp32.h"
ModbusMaster node;
#include <HardwareSerial.h>
#include <Arduino.h>
HardwareSerial co2SensorSerial(1);

// CO2 sensor data structures:
byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
unsigned char co2SensorResponse[9]; 
unsigned int currentCo2Value = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\n*****************HELLO*******************");
  Serial_kitdev.begin(9600, SERIAL_8N1); //Configure serial, baud rate=9600, 8N1 is meant 8 databit, None parity, 1 bitstop
  node.begin(1, Serial_kitdev); //Configure for node slave, ID slave node is 1
  
  co2SensorSerial.begin(9600, SERIAL_8N1, 16, 17);//Setup Serial for read sensor
  currentCo2Value = 0;
}
void loop()
{ 
  readCo2SensorValueToCo2Response(); //Read Co2
  validateCo2Response(); //Validate Value correct or not
  //***************READ node 1**************************
  Serial.println("");
  Serial.println("Read node 1");
  uint8_t result;

  //Read HoldingRegisters address 40001, 40002, 40003
  result = node.readHoldingRegisters(1, 3);//Read 3 register, start at address 1 (is meant 40001, 40002, 40003) 
  delay(10);
  if (result == node.ku8MBSuccess) //if read success
  {
    uint16_t data[3];
    data[0]=node.getResponseBuffer(0);
    data[1]=node.getResponseBuffer(1);
    data[2]=node.getResponseBuffer(2);
    Serial.printf("\r\nValue 40001: %d",data[0]);
    Serial.printf("\r\nValue 40002: %d",data[1]);
    Serial.printf("\r\nValue 40003: %d",data[2]);
  }
  else Serial.print("Read fail");
  delay(500); 
}

bool validateCo2Response() {
  byte crc = 0;
  for (int i = 1; i < 8; i++) {
    crc += co2SensorResponse[i];
  }
  crc = 256 - crc;
  bool valid = co2SensorResponse[0] == 0xFF && co2SensorResponse[1] == 0x86 && co2SensorResponse[8] == crc;
  if(!valid) {
    Serial.println("CRC error: " + String(crc) + "/"+ String(co2SensorResponse[8]));
  }
  return valid; 
}
//*********END Function validate value**************


//*************Function read************************
void readCo2SensorValueToCo2Response() {
  co2SensorSerial.write(cmd, 9);
  memset(co2SensorResponse, 0, 9);
  if(co2SensorSerial.available() > 1) {
    co2SensorSerial.readBytes(co2SensorResponse, 9);
  }
  Serial.print("Respond: ");
  for(byte i = 0; i < 9; i++) {
    Serial.print(co2SensorResponse[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");
}
//*************END Function read************************
