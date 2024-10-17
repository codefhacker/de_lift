#ifndef Logica_lift_H   // kijk of de libary al is gedefineert
#define Logica_lift_H   // defineer de libary

#include <Arduino.h>

class Logica {
  
  public:
    int verdieping[5] = {0,0,0,0,0};
    

    void berekenWaarNaarToe(int huidigeVerdieping, int gewensteVerdieping);

    int berekenTotaleWaarde(int sensorBoven, int sensorBeneden, int sensorIR);
    




};



#endif
