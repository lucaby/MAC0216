#include <stdio.h>
#include "maq.h"

INSTR prog[] = {

  {ACAO, MOVE,  {0,SEAST}},
  {NUM, END, {0, NEAST}},
};

int main(){
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 7, 14); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 5, prog, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 5, prog, RED);
  printf("Red team off to work.\n");

  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      printf("c: %d, had: %d \n", battlefield->grid[i][j].c, (int)(hasCrystal(battlefield->grid, i, j)));
      if(battlefield->grid[i][j].c  == (int)hasCrystal(battlefield->grid, i, j)
        || battlefield->grid[i][j] .c > 0 && (int)hasCrystal(battlefield->grid, i, j) > 0)
        printf("Sucesso, bixo.\n");
      else{
        printf("Error in %d, %d \n", i, j);
      }

    }
    printf("\n");
  }
  return 0;
  
}
