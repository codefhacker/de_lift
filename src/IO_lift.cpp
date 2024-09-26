#include "Arduino.h"
#include "IO_lift.h"

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



SegmentDisplay::SegmentDisplay(int latchPin, int clockPin, int dataPin) {
  shiftregisterLatchpin = latchPin;
  shiftregisterClockPin = clockPin;
  shiftregisterDataPin = dataPin;

}

void SegmentDisplay::setupSegmentDisplay() {
  pinMode(shiftregisterLatchpin, OUTPUT);
  pinMode(shiftregisterClockPin, OUTPUT);
  pinMode(shiftregisterDataPin, OUTPUT);

}

void SegmentDisplay::shiftOut(byte myDataOut) {
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
    case 0:{
      byte data;

      data = 0b11111110;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);



      break;
    }
    case 1:{
      byte data;

      data = 0b00011100;
      
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);
      break;
    }

    case 2:{
      byte data;

      data = 0b10111011;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);

      break;
    }

    case 3:{
      byte data;

      data = 0b10111110;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);

      break;
    }

    case 4:{
      byte data;

      data = 0b11011100;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);

      break;
    }

    case 5:{
      byte data;

      data = 0b11101110;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);

      break;
    }

    case 6:{
      byte data;

      data = 0b11101111;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);


      break;
    }

    case 7:{
      byte data;

      data = 0b00111100;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);

      break;
    }

    case 8:{
      byte data;

      data = 0b11111111;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);

      break;
    }

    case 9:{
      byte data;

      data = 0b11111110;
      digitalWrite(shiftregisterLatchpin, 0);
      shiftOut(data);
      digitalWrite(shiftregisterLatchpin, 1);

      break;
    }
  }


}
