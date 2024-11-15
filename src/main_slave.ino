#include <Wire.h>
#include "IO_lift.h"
#include "Logica_lift.h"
#define SLAVE_ADDR 1
#define ANSWERSIZE 1
Logica Logica;

IRSensor IRSensor(7);  // 7 op de pcb
SegmentDisplay SegmentDisplay(8, 12, 11); // latchpin , 
LiftKnop LiftKnop1(6, 9); // knoppin , ledpin
LiftKnop LiftKnop2(4, 5); // knoppin , ledpin

char IR_value;
char Knop_value;
int Total_value;

int statusKopBoven;
int statusKopBeneden;



void setup()
{
  Wire.begin(SLAVE_ADDR);                // join i2c bus with address #4
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  IRSensor.setupIR(); // ir sensor instellen
  SegmentDisplay.setupSegmentDisplay(); // segment display instellen
  LiftKnop1.setupPins(); // liftknop 1 instellen
  LiftKnop2.setupPins(); // liftknop 2 instellen
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);

  Serial.println("test123");
  for (int i = 0; i <=9; i++){
    SegmentDisplay.writeNumber(i);
    delay(1000);
  }
  


  
}

void loop()
{
  IR_value = IRSensor.getOutputIR();
  int knop12;
  int knop13;
  LiftKnop1.readButton();
  LiftKnop2.readButton();
  
  
  statusKopBoven = LiftKnop1.knopState;
  statusKopBeneden = LiftKnop2.knopState;
  Serial.println(statusKopBoven);
  Serial.println(statusKopBeneden);
  
  if (statusKopBeneden){
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(5, HIGH);
    
  }
  if (statusKopBoven){
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(9, HIGH);
    
    
  }
  if(IR_value == '1'){
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(9, LOW);
    digitalWrite(5, LOW);
    
  }
  if(IR_value == '0'){
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    
    
  }
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent()
{
  
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  SegmentDisplay.writeNumber(x);

}

void requestEvent() {
  IR_value = IRSensor.getOutputIR();
  Serial.println(IR_value);
  LiftKnop1.readButton();
  LiftKnop2.readButton();
  statusKopBoven = LiftKnop1.knopState;
  statusKopBeneden = LiftKnop2.knopState;
  Serial.print("ir :");
  Serial.println(IR_value);
  Serial.print("knop2 :"); 
  Serial.println(statusKopBeneden);
  
  // as expected by master
  Total_value = Logica.berekenTotaleWaarde(statusKopBoven,statusKopBeneden,IR_value);
  

  Serial.print("Sending Total_value: ");
  Serial.println(Total_value);  // Print what is being sent
  Wire.write(Total_value);  // Send the byte to the master
}
  
