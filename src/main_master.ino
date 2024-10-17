// What pins define for interrupts?
// Defined address (4,5) as i2c adresses


#include <Wire.h>
#include "Logica_lift.h"
#include <vector>
#include <stdio.h>


int t;
int c;
void setup(){
  Serial.begin(9600);
  Serial.println("test123");
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

int currentFloor = 0;
std::vector<std::vector<int>>> queue; // queue of commands
int upDown;





void loop(){

  for(int i= 0 ; i =< 5; i++) {
    setCurrentFloorLift(ReceiveSlave(i), i);
  }

  


}


void setCurrentFloorLift(int code, int floor) {
  switch (code) {

    // Lift detected
    case 1:
      currentFloor = floor;
      break;

    case 3:
      // down
      currentFloor = floor;
      queue.push_back(std::vector<int>{floor, 0});
      break;

    case 5:
      // up
      currentFloor = floor;
      queue.push_back(std::vector<int>{floor, 1});
      break;

    case 7:
      // both pressed
      currentFloor = floor;
      break;


    // no lift detected

    case 2:
      //down
      queue.push_back(std::vector<int>{floor, 0});
      break;

    case 4:
      //up
      queue.push_back(std::vector<int>{floor, 1});
      break;

    case 6:

      queue.push_back(std::vector<int>{floor,0});
      queue.push_back(std::vector<int>{floor, 1});

    break;




  }




}


int ReceiveSlave(int slavenumer)  {
  Wire.requestFrom(slavenumer, 2);
  int i = 0; //counter for each bite as it arrives
  while (Wire.available()) {
    c = Wire.read(); // every character that arrives it put in order in the empty array "t"
    
  }

  Serial.println(c);   //shows the data in the array t


  return c;
  delay(10);
}
