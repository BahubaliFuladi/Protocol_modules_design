#include<Wire.h>

int adcAddr = 0x48;
int addrConfig = 0x01;
int addrData = 0x00;
int confgVal = 0x83;
int ch[] = {0x42, 0x52, 0x62, 0x72};


void setup()
{
  pinMode(13, 1);
  Wire.begin();
  Serial.begin(9600);
  Wire.beginTransmission(adcAddr);
  Wire.write(addrConfig);
  Wire.write(ch[0]);
  Wire.write(confgVal);
  Wire.endTransmission();
}

void loop()
{
  Wire.beginTransmission(adcAddr);
  Wire.write(addrData);
  Wire.endTransmission();
  
  Wire.requestFrom(adcAddr, 2);
  while (Wire.available())   // slave may send less than requested
  {
    int MSB = Wire.read();    // receive a 1st byte
    int LSB = Wire.read();    // receive a 2nd byte
    int val = (MSB<<8)|LSB;
    Serial.print(val);        // print the character
    Serial.print(",");
    Serial.print(val,HEX);
  }
  Serial.println();

  digitalWrite(13, 1);
  delay(200);
  digitalWrite(13, 0);
  delay(200);
}

