#include <Wire.h>

byte addressI2C = 10;
int usedPins[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,A0,A1};

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<16; i++)
  {
    pinMode(usedPins[i],OUTPUT);
  }
  Wire.begin(addressI2C);
  Wire.onReceive(receiveEvent);
}

void demultiplex (byte b1, byte b2)
{
  for(int i=0; i<8; i++)
  {
    digitalWrite(usedPins[i],  ((b1 >> i)  & 0x01));
    digitalWrite(usedPins[i+8],((b2 >> i)  & 0x01));
  }
}

void receiveEvent(int howMany) {
  while (2 < Wire.available()) { // loop through all but the last
    byte b1 = Wire.read(); // receive byte as a character
    byte b2 = Wire.read(); // receive byte as a character
    demultiplex (b1, b2);
  }
  if(Wire.available())
    byte toDiscard = Wire.read(); //Discarding uneven byte
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}
