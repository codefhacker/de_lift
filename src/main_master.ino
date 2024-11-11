#include <Wire.h>
#include "IO_lift.h"
#include "Logica_lift.h"
#include <Keypad.h>

int t;
int c;
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {22, 23, 24, 25}; 
byte colPins[COLS] = {26, 27, 28, 29}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 




MotorLift MotorLift(13,12,11);
void setup()

{
  MotorLift.setupMotor();
  Serial.begin(9600);
  Serial.println("test123");
  Wire.begin(); // join i2c bus (address optional for master)
}

int x = 0;

void loop()
{
  MotorLift.controlMotor(0);
  char customKey = customKeypad.getKey();
  if (customKey){
    Serial.println(customKey);
  }

  for(int i = 1; i <=6; i++){
    Wire.beginTransmission(i); // transmit to device #4
    Wire.write(x);              // sends one byte  
    Wire.endTransmission();    // stop transmitting
  }
  x++;

  for (int i = 1; i <= 1; i++){
    ReceiveSlave(i);
  }
  
  
  //delay(1000);
  if (x >=9){
    x = 0;
  }

  
  

  
}


void ReceiveSlave(int slavenumer)  {
  Wire.requestFrom(slavenumer, 2);
  
  
  c = Wire.read(); // every character that arrives it put in order in the empty array "t"
  if (c == 1){
    MotorLift.controlMotor(2);
  }
  
  // Serial.print("recieved from : ");
  // Serial.println(slavenumer);
  // Serial.println(c);   //shows the data in the array t
  
}
