#include "vigiar_punir.h"
#include "alimentador.h"
#include "config.h"

boolean emergencia = false;
int LH = 5000; // Limited hold

const int receptor[5] = {9, 10, 11, 12, 13};
int leitura[5] = {0, 0, 0, 0, 0};

// Definição do número de casinhas consideradas
int nCas = 1;
int Cas1 = 5;
const int Cas2[2] = {3, 4};
int Cas3[3] = {3, 4, 5};
int Cas4[4] = {2, 3, 4, 5};


int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, idc = 0;

int qtdTestes = 3;

void limparVariaveis (){
  c1 = 0; c2 = 0; c3 = 0; c4 = 0; c5 = 0; idc = 0;
}

void botao_emergencia() {
  emergencia = true;
  //digitalWrite(30, LOW);
}


void rotinaPrincipal() {
  while (c1 < qtdTestes){// || c2 <= qtdTestes || c3 <= qtdTestes || c4 <= qtdTestes || c5 <= qtdTestes) {
    if (emergencia) break;
    digitalWrite(30, HIGH);
    idc = Randomiza_Casinhas();
    Vigiar_Punir(idc, LH);  
  }
  //digitalWrite(30, LOW);
}



//------------------------- Rotinas para o ciclo de teste -----------------------------------------------------------------------------------------------------------------

int Randomiza_Casinhas() {
  // Escolhe um índice aleatório em opc e soma os contadores até o fim do teste
  int val = 0, opc = 0;
  //Número de casinhas envolvidas
  while (val == 0) {
    val = 1;

    switch (nCas) {
      case 1:
        opc = Cas1 + 3;
        c1++; 
        if (c1 > qtdTestes){
          c1=qtdTestes; 
          val = 0; 
          break;
        }
        break;

      case 2:
        c3 = qtdTestes + 1;
        c4 = qtdTestes + 1;
        c5 = qtdTestes + 1;
        opc = random(1, 3);
        if (opc == 1) opc = Cas2[0] + 3;
        if (opc == 2) opc = Cas2[1] + 3;

        if (opc == Cas2[0] + 3) {
          c1++;
          if (c1 > qtdTestes) val = 0;
        }
        if (opc == Cas2[1] + 3) {
          c2++;
          if (c2 > qtdTestes) val = 0;
        }
        break;

      case 3:
        c4 = qtdTestes + 1;
        c5 = qtdTestes + 1;
        opc = random(1, 4);
        if (opc == 1) opc = Cas3[0] + 3;
        if (opc == 2) opc = Cas3[1] + 3;
        if (opc == 3) opc = Cas3[2] + 3;

        if (Cas3[0] + 3) {
          c1++;
          if (c1 > qtdTestes) val = 0;
        }
        if (Cas3[1] + 3) {
          c2++;
          if (c2 > qtdTestes) val = 0;
        }
        if (Cas3[2] + 3) {
          c3++;
          if (c3 > qtdTestes) val = 0;
        }

        break;

      case 4:
        c5 = qtdTestes + 1;
        opc = random(1, 5);
        if (opc == 1) opc = Cas4[0] + 3;
        if (opc == 2) opc = Cas4[1] + 3;
        if (opc == 3) opc = Cas4[2] + 3;
        if (opc == 4) opc = Cas4[3] + 3;

        if (opc == Cas4[0] + 3) {
          c1++;
          if (c1 > qtdTestes) val = 0;
        }
        if (opc == Cas4[1] + 3) {
          c2++;
          if (c2 > qtdTestes) val = 0;
        }
        if (opc == Cas4[2] + 3) {
          c3++;
          if (c3 > qtdTestes) val = 0;
        }
        if (opc == Cas4[3] + 3) {
          c4++;
          if (c4 > qtdTestes) val = 0;
        }
        break;

      case 5:
        opc = random(4, 9);
        switch (opc) {
          case 3: c1++; if (c1 > qtdTestes) val = 0; break;
          case 4: c2++; if (c2 > qtdTestes) val = 0; break;
          case 5: c3++; if (c3 > qtdTestes) val = 0; break;
          case 6: c4++; if (c4 > qtdTestes) val = 0; break;
          case 7: c5++; if (c5 > qtdTestes) val = 0; break;
        }
        break;
    }
  }
  return opc;
}


void Realiza_Punicao(int opc, int buzzer, int controle_buzzer, int altobrilho, int tempo_punicao) {
  digitalWrite(opc, LOW);
  tone(buzzer, controle_buzzer);
  digitalWrite(altobrilho, HIGH);
  delay(tempo_punicao);
  digitalWrite(altobrilho, LOW);
  noTone(buzzer);
}

boolean Vigiar_Punir(int opc, int tempo_espera) {
  digitalWrite(opc, HIGH);
  unsigned long contI = millis();             // INÍCIO DA CONTAGEM DO TEMPO DE RESPOSTA

  for (int i = 0; i < 50; i++) {
    //for (int e = 0; e < 5; e++) {
      leitura[4] = digitalRead(receptor[4]);
    //}
    if (leitura[0] == 1) break;
    if (leitura[1] == 1) break;
    if (leitura[2] == 1) break;
    if (leitura[3] == 1) break;
    if (leitura[4] == 1) break;
    if (emergencia) return false;
    delay(tempo_espera / 50);
    
  }
  //SE A COBAIA ACERTOU, ANOTA-SE O TEMPO DO PROCESSO E LIBERA RECOMPENSA
  if (leitura[opc - 4] == 1) {
    digitalWrite(opc, LOW);
    digitalWrite(8, HIGH);
    unsigned long contF = millis();           // FIM DA CONTAGEM DO TEMPO DE RESPOSTA
    unsigned long cont1 = (contF - contI);    // CÁLCULO DO TEMPO DE RESPOSTA
    Serial.println("Carla carla");
    if (leitura[opc - 3] == HIGH) {
      iluminaAlimentador();
    }
    leitura[opc - 3] = LOW;
  }
  //CASO ELA TENHA ATRASADO OU ERRADO, OCORRE A PUNIÇÃO
  else {
    Realiza_Punicao(opc, buzzer, controle_buzzer, altobrilho, tempo_punicao);
    iluminaAlimentador();
  }
  return false;
}
