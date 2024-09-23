#include "IO_lift.h" // importeer eigen IO lift libary 

//#define ledpin 11

//IRSensor IRSensor(12); // initaliseer infrarood sensor

SegmentDisplay SegmentDisplay(8, 12, 11); // inistaliseer shift register en segment display 


void setup() {
  //pinMode(ledpin, OUTPUT);
  Serial.begin(9600);
  //IRSensor.setupIR(); // setup infrarood sensor
  SegmentDisplay.setupSegmentDisplay();

}

void loop() {
  // bool value = IRSensor.getOutputIR(); // lees infrarood sensor
  // Serial.println(value);
  // digitalWrite(ledpin, !value);
  
  for (int i=0; i <9; i++){
    SegmentDisplay.writeNumber(i);
    delay(200);


}
}








