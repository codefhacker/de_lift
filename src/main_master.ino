#include <Arduino.h>
#include <Wire.h>
#include "ArduinoSort.h"
#include "IO_lift.h"

MotorLift MotorLift(30,31,32);

void setup() {
  MotorLift.setupMotor();
  Serial.begin (9600);
  Serial.println("initializing");
  Wire.begin(); // Join i2c bus (address optional for master)
  pinMode(6, INPUT);
}


byte x = 0;
int currentFloor = 0;
int upDown = 0;

int queueCounter = 0; // counter that shows the latest queue
int queue[25][2]; // queue of commands 

int moveQueueCounter = 0;
int moveQueue[25];

int destination;


/*
[[floor, direction]]
direction [0/1/2]
0 -> down
1 -> up
2 -> undecided
*/



void loop() {
  if (digitalRead(6) == 1) {
    MotorLift.controlMotor(0);
  }
  
  for (int i=1 ; i < 6; i++) {
    setCurrentFloorLift(ReceiveSlave(i), i-1);
  }
  transmitCurrentFloor();
  setMoveQueue();
  printQueue();
  moveLift();
 




}

void printQueue(){

  Serial.print("Updown: ");
  Serial.println(upDown);
  Serial.print("QueueCounter: ");
  Serial.println(queueCounter);
  Serial.print("CurrentFloor:   ");
  Serial.println(currentFloor);
  Serial.println("------------");
  Serial.println("QUEUE");

  for (int i = 0; i < queueCounter; i++) {
    Serial.print(queue[i][0]);
    Serial.print(". ");
    Serial.print(queue[i][1]);
    Serial.print("|");
  }

  Serial.println();
  Serial.println("----------------");
  Serial.println("MOVEQUEUE");
  for (int i = 0; i < moveQueueCounter; i++) {
    Serial.print(moveQueue[i]);
    Serial.print(". ");
    Serial.print("|");
  }
  Serial.println();
  Serial.println("----------------");


}



void setMoveQueue() {

  if(currentFloor == 0){
    upDown = 1;
  }

  if (currentFloor == 4) {
    upDown = 0;
  }

  int indexToClear[25];
  indexToClear[25] = 0; // indexToClear at element 25 is the index counter

  for (int i=0; i <= queueCounter; i++) {
    if (queue[i][0] > currentFloor && queue[i][1]==upDown && upDown == 1) {
      indexToClear[indexToClear[25]] = i;
      moveQueue[moveQueueCounter] = queue[i][0];
      moveQueueCounter++;

      indexToClear[25]++;
    }

    else if (queue[i][0] < currentFloor && queue[i][1]==upDown && upDown == 0) {
      indexToClear[indexToClear[25]] = i;
      moveQueue[moveQueueCounter] = queue[i][0];
      moveQueueCounter++;

      indexToClear[25]++;
    }
    else {
      if (moveQueueCounter <= 0) {
        if (queueCounter == 0) {
          return;
        }

        if ((currentFloor - queue[0][0]) < 0) {
          upDown = 1;
        } else {
          upDown = 0;
        }
      }
    }
  }

  // Clean up queue
  for (int i=0; i < indexToClear[25]; i++) {

    for (int target = indexToClear[i]; i < queueCounter; i++) {
      // shift and delete elements to the left and decrement the queueCounter
      queue[target][0] = queue[target+1][0];
      queue[target][1] = queue[target+1][1];
    }
    queueCounter--;

  }
  indexToClear[25] = 0;


  if (upDown == 1) {
    sortArray(moveQueue, moveQueueCounter);

  } else {
    sortArrayReverse(moveQueue,moveQueueCounter);
  }

}

void moveLift() {
  if (destination == currentFloor) {
    MotorLift.controlMotor(0);

    if (moveQueueCounter > 0) { // set new destination
      destination = moveQueue[0];

      for (int i=0; i < moveQueueCounter; i++) {
        moveQueue[i] = moveQueue[i+1]; // delete and shift
      }
      moveQueueCounter--;
      
    } else {
      return;
    }
  }

  switch(upDown) {
    case 0:
    MotorLift.controlMotor(2);
    break;


    case 1:
    MotorLift.controlMotor(1);
    break;

  }


}
 



void setCurrentFloorLift(int code, int floor) {

  switch (code) {
    
    //Lift detected
    case 1:
      currentFloor = floor;
      break;

    case 3:
      currentFloor = floor;
      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 1;
      break;

    case 5:
      currentFloor = floor;
      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 0;
      break;

    case 7:
      currentFloor = floor;
      break;


    case 2:
      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 1;
      break;
    
    case 4:
      queue[queueCounter][0] = floor;
      queue[queueCounter++][1] = 0 ;
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
  for (int i = 1; i <= 6 ; i++) {
    Wire.beginTransmission(i);
    Wire.write(currentFloor);
    Wire.endTransmission();
  }
}



int ReceiveSlave(int slavenumer)  {
  int c;
  Wire.requestFrom(slavenumer, 2);
  c = Wire.read();


  Serial.print("ReceiveSlave");
  Serial.println(slavenumer);
  Serial.println(c);   //shows the data in the array t
  Serial.println("-------");
  return c;
}