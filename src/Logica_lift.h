/*

lift libary voor de lift van groep 9

Gemaakt door Fabian Boshoven 
student nummer : 1089500

Deze libary bevat logica voor het besturen van de lift

Voorbeelden hoe je alles moet coderen is te vinden in de map voorbeelden.


zie ook de IO libary

Datum laatst gewijzigd : 13-11-2024

*/



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
