#include <stdio.h>
#include "maq.h"

INSTR prog[] = {

  {ACAO, ATTK,  {0,SEAST}},
  {NUM, PRN, {0, NEAST}},
  {ACAO, ATTK,  {0,SEAST}},
  {NUM, PRN, {0, NEAST}},
  {NUM, END, {0, NEAST}},

};

int main() {
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 50, 50); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 10, prog, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 10, prog, RED);
  printf("Red team off to work.\n");

  battlefield->exercitos[11]->x = 1;
  battlefield->exercitos[11]->y = 2;
  battlefield->grid[1][2].o.ocupado = True;
  battlefield->grid[1][2].o.team = RED;

  printf("Resposta do sysCall:\n");
  exec_maquina(battlefield, battlefield->exercitos[0], 100);

}