#include <stdio.h>
#include "maq.h"

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
  
  Atualiza(battlefield, 1000);
  
  for(int i = 0; i < 20; i += 2)
      battlefield->exercitos[i]->alive = False;
  
  for(int i = 0; i < 20; i++) {
    if(battlefield->exercitos[i]->alive)
      printf("1");
    else
      printf("0");

  }

  printf("\n");

  RemoveMortos(battlefield, BLUE);
  RemoveMortos(battlefield, RED);
  

  for(int i = 0; i < 20; i++) {

      if(battlefield->exercitos[i] != NULL)
        printf("1");
      else
        printf("0");
  }

  printf("\n");
  return 0;
  
}