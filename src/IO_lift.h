/*
lift libary voor de lift van groep 9

Gemaakt door Fabian Boshoven 
student nummer : 1089500

Deze libary versimpelt het om het shiftregister aan te sturen, de liftmotor aan te sturen en op de druknkoppen en de ir sensor uit te lezen. 

Voorbeelden hoe je alles moet coderen is te vinden in de map voorbeelden.


zie ook de Logica_lift libary voor de logica van de lift zoals het berekenen van de verdieping en het bereken van de waarde die verstuurd wordt via i2c naar de master.


Datum laatst gewijzigd : 13-10-2024

*/


#ifndef IO_lift_H   // kijk of de libary al is gedefineert
#define IO_lift_H   // defineer de libary

#include <Arduino.h>

class IRSensor {
  private:
    int sensorPin;   // sensorpin
    int outputIR;    // variabele voor opslaan output ir sensor

  public:
    IRSensor(int pin);
    void setupIR(); // setup infrarood sensor
    char getOutputIR(); // haal 0 of 1 van infarood sensor
};

class SegmentDisplay {
  private:
    int shiftregisterLatchpin;
    int shiftregisterClockPin;
    int shiftregisterDataPin;
    void shiftOut(byte myDataOut);
  
  public:
    SegmentDisplay(int latchPin, int clockPin, int dataPin);
    void setupSegmentDisplay(); // setup segment display
    void writeNumber(int displayNumber); // schrijf nummer weg naar het display displayNumber is de waarde die je wilt tonen

};


class LiftKnop {
  private:
    int LiftKnop;
    int liftLed;
    int lastButtonState = HIGH;
    int buttonState;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 30;
    
  public:
    int knopState = LOW; 
    LiftKnop(int drukknopPin, int ledPin);
    void setupPins();
    void readButton();

};


class MotorLift{
  private:
    int enablePin;
    int motorPin1;
    int motorPin2;

  public:
    MotorLift(int enablePin, int motorPin1, int motorPin2);
    void setupMotor();
    void controlMotor(int state); // 0 is stoppen, 1 is naar boven en 2 is naar beneden
};

#endif
