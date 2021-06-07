/***************************************************
   Arduino to Arduio communication using I2C
   SLAVE Cade (this code will go in slave Arduino
   Description: In this example slave code, slave will respond the master data request by sending data to master
                and will read date send by master.
                Slave name             Address
                S8                      0x08
                data received from master will be dislpayed on on-board-LED and 
                when master request the data slave will send status of switch to master
                
                Note: 1. slave address could be any 8 bit value
                      

  Author : Bahubali Fuladi
*/
#include <Wire.h>
int LED = 13;   //on board LED is connected on pin 13
int sw = 12;    // switch is connected on pin 12
int x = 0;
void setup() {
  // Define the LED pin as Output
  Serial.begin(9600);
  pinMode (LED, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  
  // Start the I2C Bus as Slave on address 8
  Wire.begin(8);  // this address must unique for slaves connected on same I2C bus
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
  // Attach a function to trigger when request for data is reveived.
  Wire.onRequest(requestEvent);
}

/********* An ISR to read the received data *************/
void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
}
void loop() {
  //display the received data on LED
  if (x == 0) {
    digitalWrite(LED, HIGH);    //LED = ON if 0 is received
  }
  
  if (x == 1) {
    digitalWrite(LED, 0);   //LED = OFF if 1 is received
  }
}

/********* An ISR to send data to master *************/
void requestEvent() {
  if (digitalRead(sw))  //reading status of switch 
  {
    Wire.write(0x04); // send 04 (some valve) to master for off switch
    Serial.println("sw = OFF");
  }
  else
  {
    Wire.write(0x05); // send 05 (some other valve) to master for on switch
    Serial.println("sw = ON");
  }

  // as expected by master
}
