#include <Wire.h>
#define INTERRUPT_PIN 2


//  Master Code 
volatile boolean l1 = false;


void setup() {
  pinMode(INTERRUPT_PIN, INPUT_PULLUP); // Pin on input pullup mode
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), interruptFlag,FALLING); // Since pin is pulled high,  
  Wire.begin();
  
}


void interruptFlag() {
  l1 = true;
}

void readFrom(int address) {
    Wire.requestFrom(address,3);

    while (Wire.available()) {
      char c = Wire.read();
      Serial.print(c);
    }
  
  Serial.println(); 
  // Stop reading and reset flag
  l1 = false;
}



void loop() {
  
  if (l1 == true) {
    readFrom(1);
  }  

}
