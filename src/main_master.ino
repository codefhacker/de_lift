// What pins define for interrupts?
// Defined address (4,5) as i2c adresses


#include <Wire.h>
#include "Logica_lift.h"
#include <vector>


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
/*
[[<floor>, 0(down)/1(up)], [<floor>, 0/1], etc.....] 
*/

std::vector<std::vector<<int>>> moveQueue;



int upDown; // 0 -> down, 1 -> up (2 for undecided direction?)


void loop(){

  for(int i= 0 ; i =< 5; i++) {
    setCurrentFloorLift(ReceiveSlave(i), i);
  }


  transmitCurrentFloor();



}


void move() {
  // stub for movement of the lift

  
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
      queue.push_back(std::vector<int>{floor,1});

    break;

  }
}



void transmitCurrentFloor() {
  for (int i = 0; i =< 5 ; i++) {
    Wire.beginTransmission(i);
    Wire.write(currentFloor)
    Wire.endTransmission();
  }
}


void determineDestination() { // TODO may have it return a list of movement instead.....
  // if max and or lowest

  if (currentFloor = 0) {
    upDown = 1;
  }

  if (currentFloor = 5) {
    upDown = 0;
  }



  // Grab all the requests above and below
  std::vector<std::vector<int>> above;
  std::vector<std::vector<int>> below;
  std::vector<int> highest;
  std::vector<int> lowest;

  // TODO -> up and down button requests, now it's just navigation

  for (auto request : queue) {
    if (request[0] > currentFloor ) {
      above.push_back(request);
      if (request[1] > highest) {
        highest = request;
      }

    } else {
      below.push_back(request);
      if(request[1] < lowest) {
        lowest = request;
      }
    }
  }


  // TODO filter based on the movement.
  if (upDown == 0) {
    // here be side effects.
    moveQueue.insert(moveQueue.begin(), below.begin(), below.end() )
    // move to lowest, but base that off of movequeue
    // move (lowest)

  } else if (upDown == 1) { // above direction
    moveQueue.insert(moveQueue.begin(), above.begin(), above.end() );

    // TODO sort the direction and add the highest or lowest to the end
  
  } else {
    moveQueue.insert(queue.begin());
    
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
