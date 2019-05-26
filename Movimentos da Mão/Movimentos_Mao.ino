//Adiciona a biblioteca para controle dos servos
#include <VarSpeedServo.h>
//Define o nome para os servos
VarSpeedServo polegarFlexao;
VarSpeedServo polegarRotacao;
VarSpeedServo indicador;
VarSpeedServo medio;
VarSpeedServo anelar;
VarSpeedServo minimo;
VarSpeedServo pulsoDireita;
VarSpeedServo pulsoEsquerda;

const int pinSensorLDR = 10;

#define tempoEntreContracao 200 //milisegundos
#define tempoMaximoEntreContracao 800 //milisegundos

// Declaração das variaveis

int contaContracao = 0;
unsigned long tempoEspera = 0;
unsigned long tempoEsperaEntreContracao = 0;

// Declaração da função
void executarAcao();

void setup() {

  Serial.begin(9600);

  // Definindo modo dos pinos e as portas de entradas dos componentes
  pinMode(pinSensorLDR, INPUT);
  polegarFlexao.attach(6);
  polegarRotacao.attach(7);
  indicador.attach(5); 
  medio.attach(4);
  anelar.attach(3);
  minimo.attach(2);
  pulsoDireita.attach(8);
  pulsoEsquerda.attach(9);

   //abrir mão
   indicador.slowmove(25, 60);
   medio.slowmove(90, 50);
   anelar.slowmove(90, 50);
   minimo.slowmove(95, 50);
   polegarRotacao.slowmove(20, 90);
   polegarFlexao.slowmove(20, 90);
   delay(1000);

   //Fechar a mão
   indicador.slowmove(75, 40);//30
   medio.slowmove(20, 50);
   anelar.slowmove(20, 50);
   minimo.slowmove(20, 60);//50       
   polegarRotacao.slowmove(160, 90);
   delay(500);
   polegarFlexao.slowmove(65, 40);
   delay(2000);

   //Abrir Dedos Individualmente
   polegarRotacao.slowmove(20, 90);
   polegarFlexao.slowmove(20, 90);
   delay(1000);
   indicador.slowmove(25, 60);
   delay(1000);
   medio.slowmove(90, 50);
   delay(1000);
   anelar.slowmove(90, 50);
   delay(1000);
   minimo.slowmove(95, 50);
   delay(2000);

   // Pinça fechar
   polegarRotacao.slowmove(155, 90);
   polegarFlexao.slowmove(48, 90);
   delay(500);
   indicador.slowmove(55, 30); 
   delay(2000);

   // Pinça abrir
   indicador.slowmove(25, 60);
   polegarRotacao.slowmove(20, 90);
   polegarFlexao.slowmove(20, 90);
   delay(2000);

   //Fechar a mão
   indicador.slowmove(75, 40);//30
   medio.slowmove(20, 50);
   anelar.slowmove(20, 50);
   minimo.slowmove(20, 60);//50       
   polegarRotacao.slowmove(160, 90);
   delay(500);
   polegarFlexao.slowmove(65, 40);
   delay(1000);

   //abrir mão
   indicador.slowmove(25, 60);
   medio.slowmove(90, 50);
   anelar.slowmove(90, 50);
   minimo.slowmove(95, 50);
   polegarRotacao.slowmove(20, 90);
   polegarFlexao.slowmove(20, 90);
  
   Serial.println("Setup Concluído");
}

void loop() {
  //Verifica o estado do Sensor, ao detectar o sinal mudando para HIGH
  static int sensorLDRAnt;
  int sensorLDR = digitalRead(pinSensorLDR);
  
  //Se o sensor detectar mudança do estado LOW para HIGH
  if ((sensorLDR == HIGH) && (sensorLDRAnt == LOW)) {
    Serial.print("\n detectou");

    //Calcula o tempo da ultima mudança para nãi detctar o mesmo sinal
    if ((millis() - tempoEspera) > tempoEntreContracao) {
      tempoEspera = millis(); // Atualiza o tempo
      tempoEsperaEntreContracao = millis(); // Atualiza o tempo para controle da Contagem
      contaContracao++;
    }
  }
  sensorLDRAnt = sensorLDR;

  // Caso exceda o tempo de controle da contagem, Executa a Ação e zera a contagem
  if ( (contaContracao != 0) && ((millis() - tempoEsperaEntreContracao) > tempoMaximoEntreContracao) ) {
    executarAcao();
    contaContracao = 0;
    tempoEsperaEntreContracao = millis();
  }

}


void executarAcao() {

  switch (contaContracao){
    case 1:
    //Abrir Mão
       indicador.slowmove(25, 40);
       medio.slowmove(90, 40);
       anelar.slowmove(90, 40);
       minimo.slowmove(95, 40);
       polegarRotacao.slowmove(20, 90);
       polegarFlexao.slowmove(20, 90);
       Serial.print("\n O Total de contracao foi de:  ");
       Serial.println(contaContracao);
       break;
    case 2:
    //Fechar mão
       indicador.slowmove(75, 30);
       medio.slowmove(20, 40);
       anelar.slowmove(20, 40);
       minimo.slowmove(20, 50);       
       polegarRotacao.slowmove(160, 90);
       delay(500);
       polegarFlexao.slowmove(65, 40);
       Serial.print("\n O Total de contracao foi de:  ");
       Serial.println(contaContracao);
      break;
    default:
       Serial.print("\n O Total de contracao foi de:  ");
       Serial.println(contaContracao);
  }
}
