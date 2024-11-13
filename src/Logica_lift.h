#ifndef Logica_lift_H   // kijk of de libary al is gedefineert
#define Logica_lift_H   // defineer de libary

#include <Arduino.h>

class Logica {
  
  public:
    int verdieping[5] = {0,0,0,0,0};
    int huidigeVerdieping = 0;
    int motorRichting = 0;
    int slavenummer = 0;
    int wachtrij[10];
    int wachtrijCount;
    long currentTime = 0;
    long bGTimer = 5000;  
    

    void berekenWaarNaarToe(int huidigeVerdieping, int gewensteVerdieping);

    int berekenTotaleWaarde(int sensorBoven, int sensorBeneden, char sensorIR);
    




};



#endif
