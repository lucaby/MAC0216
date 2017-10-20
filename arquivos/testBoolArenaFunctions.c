#include <stdio.h>
#include "maq.h"

INSTR prog[] = {

  {ACAO, MOVE,  {0,EAST}},
  {ACAO, MOVE,  {0,NEAST}},
  {ACAO, GRAB,  {0,WEST}},
  {ACAO, ATTK,  {0,EAST}},
  {ACAO, DEPO,  {0,WEST}},
  {ACAO, GRAB,  {0,WEST}},
  {INTER, PUSH, {0, WEST}},
  {NUM, ATR,  {3, NEAST}},
  {NUM, PRN, {0,NEAST}},
  {INTER, PUSH,  {0,WEST}},
  {NUM, ATR,  {2, NEAST}},
  {NUM, PRN, {0, NEAST}},
  {INTER, PUSH,  {0,WEST}},
  {NUM, ATR,  {1, NEAST}},
  {NUM, PRN, {0, NEAST}},
  {INTER, PUSH,  {0,WEST}},
  {NUM, ATR, {0,NEAST}},
  {NUM, PRN, {0,NEAST}},
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

  exec_maquina(battlefield, battlefield->exercitos[0], 1000);
}