/**********************************************
 * I2C based ADC (ADS1115) interfacing with 
 * Arduino;
 * Author: Bahubali Fuladi
 */
#include<Wire.h> //library for I2C

int adcAddr = 0x48;     //address of ADS1115 ic
int addrConfig = 0x01;  //address of config reg of ADS1115
int addrData = 0x00;    //address of data reg of ADS1115
int confgVal = 0x83;    //value to be put in config reg
int ch[] = {0x42, 0x52, 0x62, 0x72};    //value for analog input channel selection


void setup()
{
 
  Wire.begin();     //initiate the Arduino I2C
  Serial.begin(9600); //initiate Arduino UART

  /******* this is to congiger  ADS1115 *************/
  Wire.beginTransmission(adcAddr);    //Start i2c communication with ADS1115 using it's address
  Wire.write(addrConfig);             //sending addr. of configuration config. reg. to write config value in it
  Wire.write(ch[0]);                  //1st config byte to select analog channel
                                      //ch[1] = ch1 ; ch[2] = ch2; ch[3] = ch3
  Wire.write(confgVal);               //2nd config byte
  Wire.endTransmission();             // end i2c communication.
}

void loop()
{
  /****** this is to read converted data form ADS1115 *********/
  Wire.beginTransmission(adcAddr); //Start i2c communication with ADS1115 using it's address
  Wire.write(addrData);            //sending the address of data reg. 
  Wire.endTransmission();          //end comm.
  
  Wire.requestFrom(adcAddr, 2);    //request 16 bit data from ADS1115
  while (Wire.available())          // loop to read all data send by adc back to arduino
  {
    int MSB = Wire.read();    // receive a 1st byte
    int LSB = Wire.read();    // receive a 2nd byte
    int val = (MSB<<8)|LSB;   //joining 1st and 2nd byte
    Serial.print(val);        // print the in decimal
    Serial.print(",");
    Serial.print(val,HEX);    //print the value in HEX
  }
  Serial.println();
  delay(500);
}


