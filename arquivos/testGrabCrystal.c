#include <stdio.h>
#include "maq.h"

INSTR prog[] = {

  {ACAO, GRAB,  {0,SEAST}},
  {NUM, PRN, {0, NEAST}},
  {ACAO, GRAB,  {0,SEAST}},
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

  InsereExercito(battlefield, 5, prog, RED);
  printf("Red team off to work.\n");


  if(battlefield->grid[1][2].c == 0)
    battlefield->grid[1][2].c++;
  else if(battlefield->grid[1][2].c > 1)
    battlefield->grid[1][2].c = 1;

  printf("Crystals  bf: %d\n", battlefield->grid[1][2].c);
  printf("Resposta do sysCall:\n");
  exec_maquina(battlefield, battlefield->exercitos[0], 100);
  printf("Crystals after: %d\n", battlefield->grid[1][2].c);

}