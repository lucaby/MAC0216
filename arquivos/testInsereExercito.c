#include <stdio.h>
#include "maq.h"
#include "instr.h"
//DONE
INSTR prog[] = {


  {NUM, PUSH,  9},
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
    inicializaArena(battlefield, 7, 14); 
    printf("Grid Inicializado.\n");

    InsereExercito(battlefield, 5, prog, BLUE);
    printf("Blue team off to work.\n");

    for(int i = 0; i < 5; i++){
        if(battlefield->exercitos[i] != NULL && battlefield->exercitos[i]->t == BLUE 
           && battlefield->exercitos[i]->crystals == 0 && battlefield->exercitos[i]->alive == True)
          printf("Sucesso, bixo.\n");
        else printf("Po, bixo.\n");
        }

    InsereExercito(battlefield, 5, prog, RED);
    printf("Red team off to work.\n");

    for(int i = 5; i < 10; i++){
        if(battlefield->exercitos[i] != NULL && battlefield->exercitos[i]->t == RED 
           && battlefield->exercitos[i]->crystals == 0 && battlefield->exercitos[i]->alive == True)
          printf("Sucesso, bixo.\n");
        else printf("Po, bixo.\n");

    }
  closeArena(battlefield);
  return 0;
}