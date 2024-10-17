#include <Wire.h>
#include "IO_lift.h"
#include "Logica_lift.h"
#define SLAVE_ADDR 4
#define ANSWERSIZE 1
Logica Logica;

IRSensor IRSensor(7);  // 7 op de pcb
SegmentDisplay SegmentDisplay(8, 12, 11); // latchpin , 
LiftKnop LiftKnop1(2, 4); // knoppin , ledpin
LiftKnop LiftKnop2(3, 5); // knoppin , ledpin
//MotorLift MotorLift(5,6,7);

//MotorLift MotorLift(13,12,11);

char IR_value;
char Knop_value;
int Total_value;

int statusKopBoven;
int statusKopBeneden;



void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  IRSensor.setupIR(); // ir sensor instellen
  SegmentDisplay.setupSegmentDisplay(); // segment display instellen
  LiftKnop1.setupPins(); // liftknop 1 instellen
  LiftKnop2.setupPins(); // liftknop 2 instellen
  //MotorLift.setupMotor();
  // digitalWrite(13, HIGH);
  // digitalWrite(12, 1);
  // digitalWrite(11, 0);
  
  Serial.println("test123");

  
}

void loop()
{
  //MotorLift.controlMotor(2);
  IR_value = IRSensor.getOutputIR();
  //Serial.println(IR_value);
  LiftKnop1.readButton();
  LiftKnop2.readButton();
  statusKopBoven = LiftKnop1.knopState;
  statusKopBeneden = LiftKnop2.knopState;
  //Serial.print(statusKopBoven);
  
  if (statusKopBeneden){
    digitalWrite(13, HIGH);
  }
  if(IR_value == 1){
    digitalWrite(13, LOW);
  }
  // digitalWrite(13, HIGH);
  // digitalWrite(12, 1);
  // digitalWrite(11, 0);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent()
{
  
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  //SegmentDisplay.writeNumber(x);
}

void requestEvent() {
  IR_value = IRSensor.getOutputIR();
  //Serial.println(IR_value);
  LiftKnop1.readButton();
  LiftKnop2.readButton(); 
  statusKopBoven = LiftKnop1.knopState;
  statusKopBeneden = LiftKnop2.knopState;
  // Serial.print("ir :");
  // Serial.println(IR_value);
  // Serial.print("knop2 :");
  // Serial.println(statusKopBeneden);
  
  // as expected by master
  Total_value = Logica.berekenTotaleWaarde(statusKopBoven,statusKopBeneden,IR_value);
  

  Serial.print("Sending Total_value: ");
  Serial.println(Total_value);  // Print what is being sent
  Wire.write(Total_value);  // Send the byte to the master
}
