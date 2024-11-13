#include <Wire.h>
#include "IO_lift.h"
#include "Logica_lift.h"
#include <Keypad.h>

int t;
int c;
const byte ROWS = 4; 
const byte COLS = 4; 

Logica Logica;

SegmentDisplay SegmentDisplay(8, 12, 11); // latchpin , 
LiftKnop LiftKnop1(6, 9); // knoppin , ledpin



char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {22, 23, 24, 25}; 
byte colPins[COLS] = {26, 27, 28, 29}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 




MotorLift MotorLift(30,31,32);
void setup()

{
  LiftKnop1.setupPins();
  SegmentDisplay.setupSegmentDisplay();
  MotorLift.setupMotor();
  Serial.begin(9600);
  Serial.println("test123");
  SegmentDisplay.writeNumber(2); 
  delay(1000);
  SegmentDisplay.writeNumber(3); 
  delay(1000);
  SegmentDisplay.writeNumber(4); 
  delay(1000);
  
  Wire.begin(); // join i2c bus (address optional for master)

}

int x = 0;

void loop()
{
  
  //MotorLift.controlMotor(1);
  LiftKnop1.readButton();

  int statusKopBoven = LiftKnop1.knopState;
  if(statusKopBoven){
    while(1){
      MotorLift.controlMotor(0);
      delay(10000000000);
      
    }
  }
  

  for(int i = 1; i <=6; i++){
    Wire.beginTransmission(i); // transmit to device #4
    Wire.write(Logica.huidigeVerdieping);
    SegmentDisplay.writeNumber(Logica.huidigeVerdieping);              // sends one byte  
    Wire.endTransmission();    // stop transmitting
  }
  

  for (int i = 1; i <= 5; i++){
    ReceiveSlave(i);
  }
  
  
  

  
  

  
}


void ReceiveSlave(int slavenummer)  {
  
  Wire.requestFrom(slavenummer, 2);
  
  
  c = Wire.read(); // every character that arrives it put in order in the empty array "t"
 
  
  
  if (c == 2 || c == 4){
    Logica.berekenWaarNaarToe(Logica.huidigeVerdieping,slavenummer - 1);
    MotorLift.controlMotor(Logica.motorRichting);
    Logica.slavenummer = slavenummer - 1;
  }

  if (c == 1){
    
    Logica.huidigeVerdieping = slavenummer - 1;
    Serial.println(Logica.huidigeVerdieping);
    Logica.berekenWaarNaarToe(Logica.huidigeVerdieping,Logica.slavenummer);
    MotorLift.controlMotor(Logica.motorRichting);
    //Serial.println("sensor detecteerd");
    //Serial.print("c :");
    
    
    //Serial.print("verieping :");
    Serial.print("slave :");
    Serial.println(slavenummer -1);
    SegmentDisplay.writeNumber(slavenummer -1);

    if (Logica.motorRichting == 0){
      char customKey = customKeypad.getKey();

      if (customKey == '0'){
        Logica.slavenummer = 0;

      }
      if (customKey == '1'){
        Logica.slavenummer = 1;

      }
      if (customKey == '2'){
        Logica.slavenummer = 2;

      }
      if (customKey == '2'){
        Logica.slavenummer = 2;

      }
      if (customKey == '3'){
        Logica.slavenummer = 3;

      }
      if (customKey == '4'){
        Logica.slavenummer = 4;

      }
    }
    Serial.print("array waarde : ");
    Serial.println(Logica.verdieping[slavenummer -1]);
    

    
  
  }

  
  
  //Serial.println(c);
}
  

  
  
  
  
