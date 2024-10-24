#include <Arduino.h>
#include <Wire.h>


void setup() {
  Serial.begin (9600);
  Serial.println("initializing");
  Wire.begin(); // Join i2c bus (address optional for master)
}


byte x = 0;
int currentFloor = 0;
int upDown = 0;

int queueCounter = 0; // counter that shows the latest queue
int queue[25][2]; // queue of commands 


/*
[[floor, direction]]
direction [0/1/2]
0 -> down
1 -> up
2 -> undecided
*/


void loop() {
  for (int i=0 ; i <= 5; i++) {
    setCurrentFloorLift(ReceiveSlave(i), i);
  }

  transmitCurrentFloor();
  
}
 



void setCurrentFloorLift(int code, int floor) {
  switch (code) {
    
    //Lift detected
    case 1:
      currentFloor = floor;
      break;

    case 3:
    // down pressed
      currentFloor = floor;
      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 0;
      break;

    case 5:
    //up
      currentFloor = floor;
      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 1;
      break;

    case 7:
    //Both pressed
      currentFloor = floor;
      break;


    // no lift detected
    case 2:
      // down
      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 0;
      break;
    
    case 4:
      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 1;
      break;


    case 6:
      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 0;

      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 1;

      break;
  }

}

void transmitCurrentFloor() {
  for (int i = 0; i <= 4 ; i++) {
    Wire.beginTransmission(i);
    Wire.write(currentFloor);
    Wire.endTransmission();
  }
}

int ReceiveSlave(int slavenumer)  {
  int c;
  Wire.requestFrom(slavenumer, 2);
  int i = 0; //counter for each bite as it arrives
  while (Wire.available()) {
    c = Wire.read(); // every character that arrives it put in order in the empty array "t"
    
  }

  Serial.println(c);   //shows the data in the array t


  return c;
  delay(10);
}