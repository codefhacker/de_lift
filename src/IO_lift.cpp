#include "HardwareSerial.h"
/*
lift libary voor de lift van groep 9

Gemaakt door Fabian Boshoven 
student nummer : 1089500

Deze libary versimpelt het om het shiftregister aan te sturen, de liftmotor aan te sturen en op de druknkoppen en de ir sensor uit te lezen. 

Voorbeelden hoe je alles moet coderen is te vinden in de map voorbeelden.


zie ook de Logica_lift libary voor de logica van de lift zoals het berekenen van de verdieping en het bereken van de waarde die verstuurd wordt via i2c naar de master.


Datum laatst gewijzigd : 13-10-2024

*/

#include "Arduino.h" // include de liabry arduino voor het inlezen aan aansturen van digitale pinnen zoals de functie Digitalwrite etc...
#include "IO_lift.h" // bestand met de headers voor de libary

// defineer IR sensor
IRSensor::IRSensor(int pin) {
  sensorPin = pin;
}

// Setup infrarood sensor
void IRSensor::setupIR() {
  pinMode(sensorPin, INPUT);
}

// lees de infrarood sensor en invert hem want 1 is normaal niks en 0 wel
char IRSensor::getOutputIR() {
  outputIR = digitalRead(sensorPin);  // lees de infrarood sensor
  outputIR = !outputIR;               // invert de output met !
  if (outputIR) {
    return '0';
  }else {
    return '1';
  }                    // return de waarde van de infrarood sensor
}

// defineer segmentdisplay 
SegmentDisplay::SegmentDisplay(int latchPin, int clockPin, int dataPin) {
  shiftregisterLatchpin = latchPin;
  shiftregisterClockPin = clockPin;
  shiftregisterDataPin = dataPin;

}

void SegmentDisplay::setupSegmentDisplay() { // setup segmentdisplay 
  pinMode(shiftregisterLatchpin, OUTPUT);
  pinMode(shiftregisterClockPin, OUTPUT);
  pinMode(shiftregisterDataPin, OUTPUT);

}

void SegmentDisplay::shiftOut(byte myDataOut) { // shift het register 8 plaatsen met als input binaire 8 bit data
  int i=0;
  int pinState;

  digitalWrite(shiftregisterDataPin, 0);
  digitalWrite(shiftregisterClockPin, 0);

  for (i=7; i>=0; i--)  {
    digitalWrite(shiftregisterClockPin, 0);
    
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
      }
    else {
      pinState= 0;
    }
    digitalWrite(shiftregisterDataPin, pinState);
    digitalWrite(shiftregisterClockPin, 1);
    digitalWrite(shiftregisterDataPin, 0);

  }
  digitalWrite(shiftregisterClockPin, 0);
}


void SegmentDisplay::writeNumber(int displayNumber){
  switch (displayNumber) {
    case 0:{ // nummer 0
      byte data;
      data = 0b01111111;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);
      break;
    }
    case 1:{ // nummer 1
      byte data;
      data = 0b00011100;      
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);
      break;
    }

    case 2:{ // nummer 2
      byte data;
      data = 0b10111011;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);

      break;
    }

    case 3:{ // nummer 3
      byte data;
      data = 0b10111110;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);

      break;
    }

    case 4:{ // nummer 4
      byte data;
      data = 0b11011100;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);
      break;
    }

    case 5:{ // nummer 5
      byte data;
      data = 0b11101110;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);
      break;
    }

    case 6:{ // nummer 6
      byte data;
      data = 0b11101111;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);
      break;
    }

    case 7:{ // nummer 7
      byte data;
      data = 0b00111100;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);
      break;
    }

    case 8:{ // nummer 8
      byte data;
      data = 0b11111111;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);
      break;
    }

    case 9:{ // nummer 9
      byte data;
      data = 0b11111110;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);
      break;
    }
  }


}


LiftKnop::LiftKnop(int drukknopPin, int ledPin) { // defineer liftknop
  LiftKnop = drukknopPin;
  liftLed = ledPin;
}

void LiftKnop::setupPins() {
  pinMode(LiftKnop, INPUT);
  pinMode(liftLed, OUTPUT);
}


void LiftKnop::readButton() {
  int reading = digitalRead(LiftKnop);  // Use buttonPin (the pin connected to the button)

  if (reading != lastButtonState) {
    // Reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed
    if (reading != buttonState) {
      buttonState = reading;

      // Set knopState to 1 only when the button is pressed
      if (buttonState == HIGH) {
        knopState = 1;  // Button pressed
      } else {
        knopState = 0;  // Button released
      }
    }
  }

  lastButtonState = reading;  // Update the lastButtonState
}

MotorLift::MotorLift(int enable, int Pin1, int Pin2){ // defineer pinnen liftmotor
  enablePin = enable;
  motorPin1 = Pin1;
  motorPin2 = Pin2;
}


void MotorLift::setupMotor(){
  pinMode(enablePin, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void MotorLift::controlMotor(int state){
  switch (state) {
    
    case 0: // alles uit
      digitalWrite(enablePin, 0);
      digitalWrite(motorPin1, 0);
      digitalWrite(motorPin2, 0);
      break;
    
    case 1: // lift naar boven
      digitalWrite(enablePin, 1);
      digitalWrite(motorPin1, 1);
      digitalWrite(motorPin2, 0);
      break;
      
    case 2: // lift naar beneden
      digitalWrite(enablePin, 1);
      digitalWrite(motorPin1, 0);
      digitalWrite(motorPin2, 1);
      break;
  }
}




