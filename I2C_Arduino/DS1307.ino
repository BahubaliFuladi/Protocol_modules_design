#include<Wire.h>

int Addr = 0x68;



void setup()
{
  pinMode(13, 1);
  Wire.begin();
  Serial.begin(9600);
  Wire.beginTransmission(0x68);
  Wire.write(0x00);
  Wire.write(0x10);
  Wire.endTransmission();
  

}

void loop()
{
  Wire.beginTransmission(0x68);

  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(0x68, 7);

  int second = (Wire.read());
  int minute = (Wire.read());
  int hour = (Wire.read() & 0b111111); //24 hour time
  int weekDay = (Wire.read()); //0-6 -> sunday – Saturday
  int monthDay = (Wire.read());
  int month = (Wire.read());
  int year = (Wire.read());

  Serial.print(second & 0x7F, HEX);     // print the character
  Serial.print(":");

  Serial.println();

  digitalWrite(13, 1);
  delay(200);
  digitalWrite(13, 0);
  delay(200);
}

