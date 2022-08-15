# SAEGILRO_EDU
**STEP1.**<br>
Read data sensor CO2 via serial  
<br>
We have two serial.  
*) **Serial**: use for print messenger (via USB type C)<br>
*) **Serial1**: use for communication with sensor CO2<br>
Define pin for Tx1, Rx1 in HardwareSerial.cpp<br>

In this test, we define **TX1 - IO26**, **RX1 - IO27**<br>

>#define RX1 27<br>
>#define TX1 26

Set co2SensorSerial is Serial1
>HardwareSerial co2SensorSerial(1); 
<br>

**In setup:**<br>
-Setup baudrate 115200 for Serial print<br>
>Serial.begin(115200);

-Setup baudrate 9600 for Serial1 read sensor CO2<br>
>co2SensorSerial.begin(9600, SERIAL_8N1); 
  <br>

**In loop:**<br>
-Read Co2 value
>readCo2SensorValueToCo2Response(); 

-Validate Value correct or not
  >if(validateCo2Response()) {<br>
    Value_CO2 = ((256 * (unsigned int) co2SensorResponse[2]) + (unsigned int) co2SensorResponse[3]);<br>
  }

-Calculation Value CO2
  >Value_CO2 = ((256 * (unsigned int) co2SensorResponse[2]) + (unsigned int) co2SensorResponse[3]);
  
-Print value CO2 to IDE with unit is ppm
  >Serial.printf("\r\nCO2 %d ppm",  Value_CO2);
  
-Delay 1s
  >delay(1000);//delay 1000ms

Connect USB type C to board  
Choice board is NodeMCU-32S same this picture  
<br>
![image](https://user-images.githubusercontent.com/49629370/184702152-2aed8eed-b4e9-407f-86e5-8350227128e4.png)
<br>

Click build<br>
![image](https://user-images.githubusercontent.com/49629370/184702399-c82ccb23-3b3c-4fde-92db-60a83d475c0c.png)

Click upload code<br>
![image](https://user-images.githubusercontent.com/49629370/184702631-1a216c37-ce9e-4790-9c7f-52728744fad2.png)
<br>



