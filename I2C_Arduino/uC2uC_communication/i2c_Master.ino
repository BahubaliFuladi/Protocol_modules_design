/***************************************************
 * Arduino to Arduio communication using I2C
 * MASTER Cade (this code will go in master Arduino
 * Description: In this example master code master will send(write) data to 2 slaves
 *              and read date from same 2 slaves and display it on serial monitor.
 *              Slave name             Address
 *              S8                      0x08
 *              S9                      0x09
 *              Note: 1. slave address could be any 8 bit value 
 *                    2. slave name is just a name used to display output it could be anything 
 *                    
 *Author : Bahubali Fuladi
 */
#include<Wire.h>

int x = 0;
void setup() {
  // Start the I2C Bus as Master
  Serial.begin(9600);
  Wire.begin();     //initiate the Arduino I2C
}

void loop() {
  /*************  this is to send data to slave device using there address ********/
  Wire.beginTransmission(9); // transmit to device S9
  Wire.write(x);              // sends x
  Wire.endTransmission();    // stop transmitting
  delay(500);
  Wire.beginTransmission(8); // transmit to device S8
  Wire.write(x);              // sends x
  Wire.endTransmission();    // stop transmitting

  x++; // x will toggle between 1 and 0
  x = x & 0x01;
  delay(500);
  /************* this is to read data from slave devices using there address ********/
  Wire.requestFrom(8, 1);    // request 1 bytes from slave device S8
  while (Wire.available()) { // loop to read data coming from slave S8
    char c = Wire.read(); // receive a byte as character
    if (c == 0x04)        //reading the status of switch connected on slave S8 
      Serial.print("S8 = OFF   ");         // print this if switch in OFF
    if (c == 0x05)
      Serial.print("S8 = ON    ");         // print this if switch in ON
  }
  Wire.requestFrom(9, 1);    // request 1 bytes from slave device S9

  while (Wire.available()) { // loop to read data coming from slave S9
    char c = Wire.read(); // receive a byte as character
    if (c == 0x04)        //reading the status of switch connected on slave S9
      Serial.print("S9 = OFF   ");         // print this if switch in OFF
    if (c == 0x05)
      Serial.print("S9 = ON    ");         // print this if switch in ON
  }
  Serial.println();
}
