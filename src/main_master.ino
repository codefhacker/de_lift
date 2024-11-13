#include <Wire.h>
#include "IO_lift.h"
#include "Logica_lift.h"
#include <Keypad.h>

int t;
int c;
const byte ROWS = 4; 
const byte COLS = 4; 

Logica Logica;

SegmentDisplay SegmentDisplay(8, 12, 11); // display pinnnen
LiftKnop LiftKnop1(6, 9); // knoppin , ledpin



char hexaKeys[ROWS][COLS] = { // defineren van keypad knoppen
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {22, 23, 24, 25}; // rij 1 keypad
byte colPins[COLS] = {26, 27, 28, 29}; // rij 2 keypad

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 




MotorLift MotorLift(30,31,32);
void setup()

{
  LiftKnop1.setupPins();
  pinMode(9,OUTPUT);
  digitalWrite(9, HIGH);
  SegmentDisplay.setupSegmentDisplay();
  MotorLift.setupMotor();
  Serial.begin(9600);
 
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
      

      for(int i = 1; i <=5; i++) {
        Wire.beginTransmission(i); // transmit to device #4
        Wire.write(10);
        SegmentDisplay.writeNumber(10);  
        digitalWrite(9, HIGH);            
        Wire.endTransmission();
        delay(100);    // stop transmitting
      }
      
      for(int i = 1; i <=5; i++){

      
        Wire.beginTransmission(i); // transmit to device #4
        Wire.write(11);
        SegmentDisplay.writeNumber(11);
        digitalWrite(9, LOW);              // sends one byte  
        Wire.endTransmission();
        delay(100);    // stop transmitting
        
      }
        

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
    c = Wire.read(); // Leest de inkomende data van de slave
    
    if (c == 2 || c == 4) {
        // Voeg bestemming toe en stuur lift naar die verdieping
        Logica.berekenWaarNaarToe(Logica.huidigeVerdieping, slavenummer - 1);
        MotorLift.controlMotor(Logica.motorRichting);
        Logica.slavenummer = slavenummer - 1;
    }

    if (c == 1) {
        // Werk huidige verdieping bij en verwerk verdere bestellingen
        Logica.huidigeVerdieping = slavenummer - 1;
        Serial.println(Logica.huidigeVerdieping);
        Logica.berekenWaarNaarToe(Logica.huidigeVerdieping, Logica.slavenummer);
        MotorLift.controlMotor(Logica.motorRichting);
        Serial.print("Slave: ");
        Serial.println(slavenummer - 1);
        SegmentDisplay.writeNumber(slavenummer - 1);

        // Zodra de lift stilstaat, accepteer nieuwe toetseninput
        if (Logica.motorRichting == 0) {
            char customKey = customKeypad.getKey();

            // Voeg verdieping toe aan wachtrij afhankelijk van toetseninput
            if (customKey >= '0' && customKey <= '4') {
                Logica.slavenummer = customKey - '0';
            }
        }

        Serial.print("Array waarde: ");
        Serial.println(Logica.verdieping[slavenummer - 1]);
    }
}

  

  
  
  
  
