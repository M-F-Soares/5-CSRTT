#include "alimentador.h"
#include "vigiar_punir.h"
#include "config.h"
#include <EEPROM.h>

const int recept[5] = {30, 31, 32, 33, 34};
int lei[5] = {0, 0, 0, 0, 0};
int ITI = 5000; // Inter-trial interval

void iluminaAlimentador() {
  int leitura_alimentador;
  digitalWrite(ledAlimentador, HIGH);     // Acende a luz da casinha do alimentador
  acionaAlimentador();                  // Dispensa uma recompensa
  //while (!digitalRead(pinoBotao)){//leitura_alimentador == LOW) {    // Aguarda a captura da recompensa
    //leitura_alimentador = digitalRead(receptor_alimentador);
    
    delay(20);
  //}
  digitalWrite(ledAlimentador, LOW);      // Desliga a luz
 
   for (int i = 0; i < 50; i++) {
    //for (int e = 0; e < 5; e++) {
    //  lei[e] = digitalRead(recept[e]);
    //}
    if (lei[0] == 1){
      Realiza_Punicao(3, buzzer, controle_buzzer, altobrilho, tempo_punicao);
      iluminaAlimentador();
      break;
    }
    if (lei[1] == 1){
      Realiza_Punicao(3, buzzer, controle_buzzer, altobrilho, tempo_punicao);
      iluminaAlimentador();
      break;
    }
    if (lei[2] == 1){
      Realiza_Punicao(3, buzzer, controle_buzzer, altobrilho, tempo_punicao);
      iluminaAlimentador();
      break;
    }
    if (lei[3] == 1){
      Realiza_Punicao(3, buzzer, controle_buzzer, altobrilho, tempo_punicao);
      iluminaAlimentador();
      break;
    }
    if (lei[4] == 1){
      Realiza_Punicao(3, buzzer, controle_buzzer, altobrilho, tempo_punicao);
      iluminaAlimentador();
      break;
    }
    delay(ITI/50);
  }
}

// Gravação na EEPROM para segurança no acionamento do motor

#define qtdBytes sizeof(unsigned long)

unsigned long contI;
unsigned long contF;
unsigned long cont1;
unsigned long limWrite = 99000;

void writeEEPROM(int addr, unsigned long value) {
  unsigned long newValue;
  int newAddr;
  byte array_bytes[qtdBytes];
  if (value >= limWrite) {
    newValue = value % limWrite;
    newAddr = int(value % limWrite);
    writeEEPROM((addr + 8)*newAddr, newValue);
  }
  for (int i = 0; i < qtdBytes; i++) {
    array_bytes[i] = ((value & ((unsigned long)0xFF << (i * 8))) >> (i * 8));
    EEPROM.write(addr, array_bytes[i]);
    addr++;
  }
}

unsigned long readEEPROM(int addr) {
  unsigned long readValue = 0;
  for (int j = 0; j < qtdBytes; j++) {
    readValue += ((unsigned long)EEPROM.read(addr + j) << (j * 8));
  }
  return readValue;
}

//------------------------- Rotinas para o Alimentador ------------------------------------------------------------------------------------------------------------------

/* SAÍDAS ANALÓGICAS/BOBINA DO MOTOR
   A0=A1
   A1=A2
   A2=B1
   A3=B2*/
const int a1 = 36, b1 = 39, a2 = 40, b2 = 41;
const unsigned long motor_EEPROM;
int k = 0;

void acionaAlimentador() {
  digitalWrite(42, HIGH);
  delay(3000);
  digitalWrite(42, LOW);
  
//  for (int i = 0 + k; i <= 25 + k; i++) {
//    delay(25);
//    if ((i + 4) % 4 == 0) {
//      digitalWrite(a1, HIGH);
//      digitalWrite(b1, LOW);
//      digitalWrite(a2, LOW);
//      digitalWrite(b2, LOW);
//    }
//
//    if ((i + 4) % 4 == 1) {
//      digitalWrite(a1, LOW);
//      digitalWrite(b1, HIGH);
//      digitalWrite(a2, LOW);
//      digitalWrite(b2, LOW);
//    }
//
//    if ((i + 4) % 4 == 2) {
//      digitalWrite(a1, LOW);
//      digitalWrite(b1, LOW);
//      digitalWrite(a2, HIGH);
//      digitalWrite(b2, LOW);
//    }
//
//    if ((i + 4) % 4 == 3) {
//      digitalWrite(a1, LOW);
//      digitalWrite(b1, LOW);
//      digitalWrite(a2, LOW);
//      digitalWrite(b2, HIGH);
//    }
//    k += 1;
//    writeEEPROM(0, motor_EEPROM);
//  }
}
