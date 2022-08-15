#include "HardwareSerial.h"
#include <Arduino.h>
HardwareSerial co2SensorSerial(1);

// CO2 sensor data structures:
byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
unsigned char co2SensorResponse[9]; 
unsigned int currentCo2Value = 0;

void setup() {
  Serial.begin(115200);//Setup baudrate for print
  co2SensorSerial.begin(9600, SERIAL_8N1);//Setup Serial for read sensor
  currentCo2Value = 0;
}
int Value_CO2=0;
void loop() 
{
  readCo2SensorValueToCo2Response(); //Read Co2
  if(validateCo2Response()) {//Validate Value correct or not
    Value_CO2 = ((256 * (unsigned int) co2SensorResponse[2]) + (unsigned int) co2SensorResponse[3]);
  }
  Serial.printf("\r\nCO2 %d ppm",  Value_CO2);
  delay(1000);//timeout between reads - in msec 
}


//*************Function validate value******************
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
}
//*************END Function read************************
