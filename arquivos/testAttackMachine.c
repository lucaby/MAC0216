#include <stdio.h>
#include "maq.h"
INSTR progR[] = {
};
INSTR progB[] = {
  {ACAO, MOVE, {0,SWEST}},
  {ACAO, MOVE, {0,SWEST}},
  {ACAO, MOVE, {0,SWEST}},
  {ACAO, ATTK, {0, SWEST}},
  {ACAO, ATTK, {0, SWEST}},
  {ACAO, ATTK, {0, SWEST}},
  {ACAO, ATTK, {0, SWEST}},
  {ACAO, ATTK, {0, SWEST}},
  {ACAO, ATTK, {0, SWEST}},
  {ACAO, ATTK, {0, SWEST}},
  {ACAO, ATTK, {0, SWEST}},
  {ACAO, ATTK, {0, SWEST}},
  {NUM, END, {0, SEAST}}

};

int main() {
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 7, 14); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 5, progB, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 5, progR, RED);
  printf("Red team off to work.\n");
  for(int i = 0; i < 20; i++)
    Atualiza(battlefield, 1);
  

}