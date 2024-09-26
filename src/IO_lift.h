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

    
    void setupSegmentDisplay(); // setup infrarood sensor

    void writeNumber(int displayNumber);
   

   
    
};

#endif
