#include <stdio.h>
#include "maq.h"
#include "arena.h"

INSTR prog[] = {


  {NUM, PUSH, { 9, WEST }},
  {NUM, CALL, { 4, WEST }},
  {NUM, PRN, { 0, WEST }},
  {NUM, END, { 0, WEST }},
  {NUM, ALC, { 1, WEST }},
  {NUM, DUP, { 0, WEST }},
  {NUM, STL, { 0, WEST }},
  {NUM, PUSH, { 1, WEST }},
  {NUM, EQ, { 0, WEST }},
  {NUM, JIF, { 13, WEST }},
  {NUM, PUSH, { 1, WEST }},
  {NUM, FRE, { 1, WEST }},
  {NUM, RET, { 0, WEST }},
  {NUM, RCE, { 0, WEST }},
  {NUM, PUSH, { 1, WEST }},
  {NUM, SUB, { 0, WEST }},
  {NUM, CALL, { 4, WEST }},
  {NUM, RCE, { 0, WEST }},
  {NUM, MUL, { 0, WEST }},
  {NUM, FRE, { 1, WEST }},
  {NUM, RET, { 0, WEST }},
  {ACAO, ATTK, { 0, NEAST }},
  {INTER, PUSH, { 0, NWEST }},
};

int main(){
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 50, 50); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 10, prog, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 10, prog, RED);
  printf("OIE");
  printf("Red team off to work.\n");
  
  for(int i = 0; i < 100; i++)
      Atualiza(battlefield, 100);
  
  for(int i = 0; i < 20; i += 2)
      battlefield->exercitos[i]->alive = False;
  
  for(int i = 0; i < 20; i++) {
    printf("%d", (int)battlefield->exercitos[i]->alive);
  }

  printf("\n");

  RemoveMortos(battlefield, BLUE);
  RemoveMortos(battlefield, RED);
  

  printf("\n");
  for(int i = 0; i < 20; i++) {
      if(battlefield->exercitos[i] != NULL)
        printf("1");
      else
        printf("0");
  }
  printf("\n");
  return 0;
  
}