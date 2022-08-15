#include "kitdevesp32.h"
ModbusMaster node;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\n*****************HELLO*******************");
  Serial_kitdev.begin(9600, SERIAL_8N1); //Configure serial, baud rate=9600, 8N1 is meant 8 databit, None parity, 1 bitstop
  node.begin(1, Serial_kitdev); //Configure for node slave, ID slave node is 1
}
void loop()
{ 
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
