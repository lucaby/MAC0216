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
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 50, 50); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 10, prog, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 10, prog, RED);
  printf("Red team off to work.\n");

  for(int i = 0; i < 100; i++){
    for(int j = 0; j < 100; j++){
      printf("Terreno: %d", battlefield->grid[i][j].t);
      printf("Base Y/N: %d", battlefield->grid[i][j].b.isBase);
      printf("Base WHOM: %d", battlefield->grid[i][j].b.team);
      printf("Cristais: %d", battlefield->grid[i][j].c);
      printf("Ocupado Y/N: %d", battlefield->grid[i][j].o.ocupado);
      printf("Ocupado WHO: %d", battlefield->grid[i][j].o.team);


      printf();
      if(battlefield->grid[i][j].c && hasCrystal(battlefield.grid, i, j))
        printf("Sucesso, bixo.\n");
      else
        printf("fug\n");
      printf();


    }
  }
  return 0;
  
}
Bool hasCrystal(Grid g, int i, int j);

Bool hasEnemy(Grid g, int i, int j, Time friendly);

Bool notOcupied(Grid g, int i, int j);