#include "HardwareSerial.h"
#include "Arduino.h"
#include "Logica_lift.h"



void Logica::berekenWaarNaarToe(int huidigeVerdieping, int slaveVerdieping){
      Serial.print("huidige verdieping : ");
      Serial.println(huidigeVerdieping);
      Serial.print("slaveverdieping : ");
      Serial.println(slaveVerdieping);
      if(huidigeVerdieping == slaveVerdieping){
        Logica::motorRichting = 0;
        Logica::slavenummer = Logica::huidigeVerdieping;
        Logica::huidigeVerdieping = Logica::slavenummer;
        Serial.print("ik ben 0 !!!!!");
        
      }
      else {
        int verschil = slaveVerdieping - huidigeVerdieping;
        if (slaveVerdieping >=0 && slaveVerdieping <=4){
          verdieping[slaveVerdieping -1] = 1;
        }
        if(verschil <= -1 && verschil >= -4 && verschil != 0){
          Logica::motorRichting = 2;
          Serial.println("ik ga naar beneden");
          

        }
        if(verschil >= 1 && verschil <= 4 && verschil != 0){
          Logica::motorRichting = 1;
          Serial.println("ik ga naar boven");
          
        }

        
        Serial.print("verschil : ");
        Serial.println(verschil);
        Serial.print("huidige verdieping : ");
        Serial.println(huidigeVerdieping);
        //Serial.print("slave nummer : ");
        //Serial.println(slaveVerdieping);
      }

      
      
}


int Logica::berekenTotaleWaarde(int sensorBoven, int sensorBeneden, char sensorIR){
  int Total_value;
  if(sensorBoven == 0 && sensorBeneden == 0 && sensorIR == '0') { 
    Total_value = 0;
    return Total_value;
  }
  else if (sensorBoven == 0 && sensorBeneden == 0 && sensorIR == '1') { 
    Total_value = 1;
    return Total_value;
    
  }
  else if (sensorBoven == 0 && sensorBeneden == 1 && sensorIR == '0') { 
    Total_value = 2;
    return Total_value;
  }
  else if (sensorBoven == 0 && sensorBeneden == 1 && sensorIR == '1') { 
    Total_value = 3;
    return Total_value;
  }
  if(sensorBoven == 1 && sensorBeneden == 0 && sensorIR == '0') { 
    Total_value = 4;
    return Total_value;
  }
  else if (sensorBoven == 1 && sensorBeneden == 0 && sensorIR == '1') { 
    Total_value = 5;
    return Total_value;
  }
  else if (sensorBoven == 1 && sensorBeneden == 1 && sensorIR == '0') { 
    Total_value = 6;
    return Total_value;
  }
  else if (sensorBoven == 1 && sensorBeneden == 1 && sensorIR == '1') { 
    Total_value = 7;
    return Total_value;
  }

}
