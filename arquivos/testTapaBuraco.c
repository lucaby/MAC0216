#include <stdio.h>
#include "maq.h"

INSTR prog[] = {

  {ACAO, MOVE,  {0,SEAST}},
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
  
  for(int i = 0; i < battlefield->firstFree; i++){
    battlefield->exercitos[i] = NULL;
  }

  battlefield->firstFree = tapaBuraco(battlefield->exercitos, battlefield->firstFree);
  printf("First free after eliminating all armies: %d \n", battlefield->firstFree);

  InsereExercito(battlefield, 50, prog, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 20, prog, RED);
  printf("Red team off to work.\n");

  for(int i = 0; i < battlefield->firstFree; i += 5){
    battlefield->exercitos[i] = NULL;
  }

  battlefield->firstFree = tapaBuraco(battlefield->exercitos, battlefield->firstFree);
  printf("First free after eliminating all armies: %d \n", battlefield->firstFree);

  for(int i = 0; i < battlefield->firstFree; i += 3){
    battlefield->exercitos[i] = NULL;
  }

  battlefield->firstFree = tapaBuraco(battlefield->exercitos, battlefield->firstFree);
  printf("First free after eliminating all armies: %d \n", battlefield->firstFree);

  for(int i = battlefield->firstFree/2; i < battlefield->firstFree; i++){
    battlefield->exercitos[i] = NULL;
  }

  battlefield->firstFree = tapaBuraco(battlefield->exercitos, battlefield->firstFree);
  printf("First free after eliminating all armies: %d \n", battlefield->firstFree);
}