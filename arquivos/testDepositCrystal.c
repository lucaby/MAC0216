#include <stdio.h>
#include "maq.h"

INSTR prog[] = {

  {ACAO, DEPO,  {0,SEAST}},
  {NUM, PRN, {0, NEAST}},
  {ACAO, DEPO,  {0,SEAST}},
  {NUM, PRN, {0, NEAST}},
  {NUM, END, {0, NEAST}},

};

int main() {
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 7, 14); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 5, prog, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 10, prog, RED);
  printf("Red team off to work.\n");


  if(battlefield->exercitos[0]->crystals == 0)
    battlefield->exercitos[0]->crystals++;

  printf("Crystals  bf: %d\n", battlefield->exercitos[0]->crystals);
  printf("Resposta do sysCall:\n");
  exec_maquina(battlefield, battlefield->exercitos[0], 100);
  printf("Crystals after: %d\n", battlefield->exercitos[0]->crystals);

}