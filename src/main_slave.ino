#include <Wire.h>
#include "IO_lift.h"
#define SLAVE_ADDR 4
#define ANSWERSIZE 1


IRSensor IRSensor(12);
char IR_value;
char Knop_value;
char Total_value;
char verdieping[] = {IR_value, "1", "2", "3", "4"};
int v = 0;




void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  IRSensor.setupIR();
  
}

void loop()
{
  delay(100);
  IR_value = IRSensor.getOutputIR();
  Serial.println(IR_value);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer


}

void requestEvent() {

  // as expected by master
  if(IR_value == '0' && Knop_value == '0') { 
    Total_value = '0';
  }
  else if (IR_value == '0' && Knop_value == '1') { 
    Total_value = '1';
  }
  else if (IR_value == '1' && Knop_value == '0') { 
    Total_value = '2';
  }
  else if (IR_value == '1' && Knop_value == '1') { 
    Total_value = '3'
  }
  Wire.write(Total_value);

}
