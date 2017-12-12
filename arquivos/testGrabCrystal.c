#include <stdio.h>
#include "maq.h"
//TODO
INSTR prog[] = {

  {ACAO, GRAB,  {0,SEAST}},
  {ACAO, GRAB,  {0,SEAST}},
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

  printf("Crystals  bf: %d\n", battlefield->grid[1][2].c);
  for(int i = 0; i < 11; i++) Atualiza(battlefield, 1);
  printf("Crystals after: %d\n", battlefield->grid[1][2].c);

}