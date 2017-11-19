#include <stdio.h>
#include "maq.h"

INSTR prog[] = {

  {ACAO, MOVE,  {0,SEAST}},
  {NUM, END, {0, NEAST}},

};

int main() {
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 7, 14); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 5, prog, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 5, prog, RED);
  printf("Red team off to work.\n");
  printf("%d %d ", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y);
  exec_maquina(battlefield, battlefield->exercitos[0], 1000);
  printf("\n%d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y);
}