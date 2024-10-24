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
    
  }
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
      
      break;
  }


}
