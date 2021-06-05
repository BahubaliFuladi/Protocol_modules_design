#include<ADS1115_WE.h>
#include<Wire.h>
#define I2C_ADDRESS 0x48

ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  if (!adc.init()) {
    Serial.println("ADS1115 not connected!");
  }
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc.setCompareChannels(ADS1115_COMP_0_GND);
  adc.setMeasureMode(ADS1115_CONTINUOUS);
}
void loop() {
  // put your main code here, to run repeatedly:
  float  voltage;
  voltage = readChannel(ADS1115_COMP_0_GND);
  Serial.println(voltage);
  delay(500);
}

float readChannel(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}
