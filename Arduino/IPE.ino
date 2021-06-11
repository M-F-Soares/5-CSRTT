#include <math.h>
#include "alimentador.h"
#include "vigiar_punir.h"
#include "config.h"

bool botao = false;
bool inicio = true;              // Verifica se é a primeira vez que a caixa foi acionada
bool final_teste = false;

void setup() {
  pinMode(pinoBotao, INPUT);       // PINO DIGITAL 16
  pinMode(ledAlimentador, OUTPUT);  // PINO DIGITAL 15
  pinMode(altobrilho, OUTPUT);      // PINO DIGITAL 50
  pinMode(buzzer, OUTPUT);          // PINO DIGITAL 2

  pinMode(30, OUTPUT);  // deletar

  Serial.begin(9600);


  //pinMode(3, OUTPUT);           // LEDS DE INDICAÇÃO DAS CASINHAS
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);

  pinMode(42, OUTPUT);

  //INPUTS
  pinMode(9, INPUT);            // RECEPTORES INFRA-VERMELHO
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, INPUT);           //RECEPTOR CAIXA DE ALIMENTAÇÃO

  attachInterrupt(digitalPinToInterrupt(3), botao_emergencia, RISING);

  //ALIMENTAÇÃO RANDÔMICA
  randomSeed(analogRead(5));    //ALIMENTAÇÃO DO RANDOM
//
//  digitalWrite(4, HIGH);
//  digitalWrite(5, HIGH);
//  digitalWrite(6, HIGH);
//  digitalWrite(7, HIGH);
//  digitalWrite(8, HIGH);
//  digitalWrite(42, HIGH);
    limparVariaveis();          // Inicializa as variáveis para o teste  
}

void loop() {
  botao = digitalRead(pinoBotao);
  if (botao && !final_teste) {  // Aguarda o acionamento do sistema através do botão
    Serial.print('A');
    if (inicio) {               // Rotina executada no início do teste
      //iluminaAlimentador();     // Primeira etapa
      inicio = false;
    }
    rotinaPrincipal();          // Rotina principal
    final_teste = true;
    digitalWrite(30, LOW);
    Serial.print('B');
  }
}
