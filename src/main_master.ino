#include <Wire.h>
#include "IO_lift.h"
#include "Logica_lift.h"
int t;
int c;

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
  Wire.beginTransmission(4); // transmit to device #4
  
  //Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

  // Wire.beginTransmission(2); // transmit to device #4
  
  // Wire.write("x is ");        // sends five bytes
  // Wire.write(x);              // sends one byte  
  // Wire.endTransmission();

  Wire.beginTransmission(3); // transmit to device #4
  
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();

  // Wire.beginTransmission(4); // transmit to device #4
  
  // Wire.write("x is ");        // sends five bytes
  // Wire.write(x);              // sends one byte  
  // Wire.endTransmission();

  // Wire.beginTransmission(5); // transmit to device #4
  
  // Wire.write("x is ");        // sends five bytes
  // Wire.write(x);              // sends one byte  
  // Wire.endTransmission();

  x++;
  ReceiveSlave(2);
  
  ReceiveSlave(4);
  // ReceiveSlave(2);
  // ReceiveSlave(3);
  // ReceiveSlave(4);
  // ReceiveSlave(5);

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
  
  Serial.print("recieved from : ");
  Serial.println(slavenumer);
  Serial.println(c);   //shows the data in the array t
  
}
