#include <stdio.h>
#include "maq.h"

INSTR prog[] = {

  {ACAO, MOVE,  EAST}
  {ACAO, MOVE,  NEAST}
  {ACAO, GRAB,  WEST}
  {ACAO, ATTK,  EAST}
  {ACAO, DEPO,  WEST}
  {ACAO, GRAB,  WEST}
  {VAR, PUSH, VAR,  WEST}
  {NUM, ATR,  3}
  {NUM, PRN, 0}
  {VAR, PUSH,  WEST}
  {NUM, ATR,  2}
  {NUM, PRN, 0}
  {VAR, PUSH,  WEST}
  {NUM, ATR,  1}
  {NUM, PRN, 0}
  {VAR, PUSH,  WEST}
  {NUM, ATR, 0}
  {NUM, PRN, 0}

};

int main(){
  Arena* battlefield;
  printf("Arena feita.\n");

  inicializaGrid(battlefield, 50, 50); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 10, prog, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 10, prog, RED);
  printf("Red team off to work.\n");

  for(int i = 0; i < 100; i++)
      Atualiza(battlefield, 100);

  RemoveExercito(battlefield, BLUE);
  for(int i = 0; i < 10; i++){
      if(battlefield->exercitos[i] == NULL)
        printf("Sucesso, bixo.\n");
      else
        printf("fug\n");
  }
  RemoveExercito(battlefield, RED);
  for(int i = 10; i < 20; i++){
      if(battlefield->exercitos[i] == NULL)
        printf("Sucesso, bixo.\n");
      else
        printf("fug\n");
  }

  return 0;
  
}