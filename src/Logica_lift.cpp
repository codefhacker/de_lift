#include "Arduino.h"
#include "Logica_lift.h"



void Logica::berekenWaarNaarToe(int huidigeVerdieping, int gewensteVerdieping){
      int verschil = gewensteVerdieping - huidigeVerdieping;
      if (gewensteVerdieping >=1 && gewensteVerdieping <=5){
        verdieping[gewensteVerdieping -1] = 1;
      }
      /*
      else if(huidigeVerdieping < gewensteVerdieping){ 
        naar boven
      }
      else if(huidigeVerdieping > gewensteVerdieping){ 
        naar beneden
      }

      maak variabele die 0 of 1 geeft, die we in hoofdcode kunnen aanroepen
      --> 
      */
    }


int Logica::berekenTotaleWaarde(int sensorBoven, int sensorBeneden, int sensorIR){
  int Total_value;
  if(sensorBoven == 0 && sensorBeneden == 0 && sensorIR == 0) { 
    Total_value = 0;
    return Total_value;
  }
  else if (sensorBoven == 0 && sensorBeneden == 0 && sensorIR == 1) { 
    Total_value = 1;
    return Total_value;
    
  }
  else if (sensorBoven == 0 && sensorBeneden == 1 && sensorIR == 0) { 
    Total_value = 2;
    return Total_value;
  }
  else if (sensorBoven == 0 && sensorBeneden == 1 && sensorIR == 1) { 
    Total_value = 3;
    return Total_value;
  }
  if(sensorBoven == 1 && sensorBeneden == 0 && sensorIR == 0) { 
    Total_value = 4;
    return Total_value;
  }
  else if (sensorBoven == 1 && sensorBeneden == 0 && sensorIR == 1) { 
    Total_value = 5;
    return Total_value;
  }
  else if (sensorBoven == 1 && sensorBeneden == 1 && sensorIR == 0) { 
    Total_value = 6;
    return Total_value;
  }
  else if (sensorBoven == 1 && sensorBeneden == 1 && sensorIR == 1) { 
    Total_value = 7;
    return Total_value;
  }

}
