#include <stdio.h>
#include "maq.h"
#include "instr.h"
INSTR prog[] = {


  {NUM, PUSH, 9},
  {NUM, CALL, 4},
  {NUM, PRN, 0},
  {NUM, END, 0},
  {NUM, ALC, 1},
  {NUM, DUP, 0},
  {NUM, STL, 0},
  {NUM, PUSH, 1},
  {NUM, EQ, 0},
  {NUM, JIF, 13},
  {NUM, PUSH, 1},
  {NUM, FRE, 1},
  {NUM, RET, 0},
  {NUM, RCE, 0},
  {NUM, PUSH, 1},
  {NUM, SUB, 0},
  {NUM, CALL, 4},
  {NUM, RCE, 0},	
  {NUM, MUL, 0},
  {NUM, FRE, 1},
  {NUM, RET, 0},
};

int main(){
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 50, 50); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 10, prog, BLUE);
  printf("Blue team off to work.\n");

  for(int i = 0; i < 10; i++){
      if(battlefield->exercitos[i] != NULL && battlefield->exercitos[i].t == BLUE)
        printf("Sucesso, bixo.\n");
      else
        printf("fug\n");
  }

  InsereExercito(battlefield, 10, prog, RED);
  printf("Red team off to work.\n");

  for(int i = 10; i < 20; i++){
      if(battlefield->exercitos[i] != NULL && battlefield->exercitos[i].t == RED)
        printf("Sucesso, bixo.\n");
      else
        printf("fug\n");
  }


  

  return 0;
  