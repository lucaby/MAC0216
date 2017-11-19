#include <stdio.h>
#include "maq.h"

INSTR prog[] = {

  {ACAO, MOVE,  {0,SEAST}},
  {NUM, END, {0, NEAST}},

};

int main() {
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");
  int n = 50;

  inicializaArena(battlefield, 7, 14); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 5, prog, BLUE);
  //The machine battlefield->exercitos[0] has x = 1, y = 0
  for(int i = 0; i < n; i++){
    if (i % 2 == 0) {
      for(int j = 1; j < n; j += 2) {
        battlefield->exercitos[0]->x = j;
        battlefield->exercitos[0]->y = i;
        for(int k = 0; k < 6; k++){
          int lin = -1, col = -1;
          switch(k){
            case 0:
              getPosition(battlefield->exercitos[0], WEST, &lin, &col, n, n);
              if(j > 1 && col != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(j == 0 && col != -1)
                printf("Erro WEST em %d %d\n", j, i);
              printf("Army position: %d %d; WEST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
            case 1:
              getPosition(battlefield->exercitos[0], NWEST, &lin, &col, n, n);
              if(i > 0 && j > 0 && lin != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(lin != -1 && (i <= 0 || j <= 0))
                printf("Erro NWEST em %d %d\n", j, i);
              printf("Army position: %d %d; NWEST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
            case 2:
              getPosition(battlefield->exercitos[0], NEAST, &lin, &col, n, n);
              if(i < n - 1 && j > 0 && lin != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(lin != -1 && (i <= 0 || j >= n - 1))
                printf("Erro NEAST em %d %d\n", j, i);
              printf("Army position: %d %d; NEAST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
            case 3:
              getPosition(battlefield->exercitos[0], EAST, &lin, &col, n, n);
              if(j < n - 2 && col != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(col != -1 && j >= n - 2)
                printf("Erro EAST em %d %d\n", j, i);
              printf("Army position: %d %d; EAST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);

              break;
            case 4:
              getPosition(battlefield->exercitos[0], SEAST, &lin, &col, n, n);
              if(i < n -1 && j < n -1 && lin != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(lin != -1 && (i >= n-1 || j >= n-1))
                printf("Erro SEAST em %d %d\n", j, i);
              printf("Army position: %d %d; SEAST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
            case 5:
              getPosition(battlefield->exercitos[0], SWEST, &lin, &col, n, n);
              if(i < n - 1 && j > 0 && lin != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(lin != -1 && (i >= n-1 || j <= 0))
                printf("Erro SWEST   em %d %d\n", j, i);
              printf("Army position: %d %d; SWEST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
      }     
    }
  }
}
    else {
      for(int j = 0; j < n; j += 2) {
        battlefield->exercitos[0]->x = j;
        battlefield->exercitos[0]->y = i;
        for(int k = 0; k < 6; k++){
          int lin = -1, col = -1;
          switch(k){
            case 0:
              getPosition(battlefield->exercitos[0], WEST, &lin, &col, n, n);
              if(j > 1 && col != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(j == 0 && col != -1)
                printf("Erro WEST em %d %d\n", j, i);
              printf("Army position: %d %d; WEST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
            case 1:
              getPosition(battlefield->exercitos[0], NWEST, &lin, &col, n, n);
              if(i > 0 && j > 0 && lin != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(lin != -1 && (i <= 0 || j <= 0))
                printf("Erro NWEST em %d %d\n", j, i);
              printf("Army position: %d %d; NWEST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
            case 2:
              getPosition(battlefield->exercitos[0], NEAST, &lin, &col, n, n);
              if(i < n - 1 && j > 0 && lin != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(lin != -1 && (i <= 0 || j >= n - 1))
                printf("Erro NEAST em %d %d\n", j, i);
              printf("Army position: %d %d; NEAST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
            case 3:
              getPosition(battlefield->exercitos[0], EAST, &lin, &col, n, n);
              if(j < n - 2 && col != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(col != -1 && j >= n - 2)
                printf("Erro EAST em %d %d\n", j, i);
              printf("Army position: %d %d; EAST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);

              break;
            case 4:
              getPosition(battlefield->exercitos[0], SEAST, &lin, &col, n, n);
              if(i < n -1 && j < n -1 && lin != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(lin != -1 && (i >= n-1 || j >= n-1))
                printf("Erro SEAST em %d %d\n", j, i);
              printf("Army position: %d %d; SEAST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
            case 5:
              getPosition(battlefield->exercitos[0], SWEST, &lin, &col, n, n);
              if(i < n - 1 && j > 0 && lin != -1){
                printf("Sucesso, bixo.\n");
              }
              else if(lin != -1 && (i >= n-1 || j <= 0))
                printf("Erro SWEST   em %d %d\n", j, i);
              printf("Army position: %d %d; SWEST position: %d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y, col, lin);
              break;
          }
      }
    }
  }
}
}