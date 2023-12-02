#include "EmonLib.h" 
EnergyMonitor emon1;

//Tensao da rede eletrica
int rede = 110.0;

//Pino do sensor SCT
int pino_sct = 1;


void setup() {
Serial.begin(9600);
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 1800/62 = 29. 
  emon1.current(pino_sct, 29);
}

void loop() {
  //Calcula a corrente  
  double Irms = emon1.calcIrms(1480);
  //Mostra o valor da corrente
  Serial.print("Corrente : ");
  Serial.print(Irms); // Irms

    //Calcula e mostra o valor da potencia
  Serial.print(" Potencia : ");
  Serial.println(Irms*rede);

   delay(1000);

}
