#ifndef VIGIAR_PUNIR
#define VIGIAR_PUNIR

#include "Arduino.h"


void limparVariaveis ();
void rotinaPrincipal();

int Randomiza_Casinhas();
void Realiza_Punicao(int opc, int buzzer, int controle_buzzer, int altobrilho, int tempo_punicao);
boolean Vigiar_Punir(int opc, int tempo_espera);
void botao_emergencia();

#endif
