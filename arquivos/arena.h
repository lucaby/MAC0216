#ifndef ARENA_H
#define ARENA_H

#include "pilha.h"
#include "structures.h"
#include "instr.h"
#include <stdlib.h>
#include <time.h>
//#include "maq.h"

typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip;
  int rbp;
  int x;
  int y;
  Cristais crystals;
  Bool alive;
  Time t;
} Maquina;

typedef struct {
  Grid grid;
  int tempo;
  Maquina* exercitos[MAXMEM];
  int firstFree;
} Arena;
//TEST DONE
void Atualiza(Arena *arena, int ciclos);

int tapaBuraco(Maquina* m[],int firstFree);

//TEST DONE
void InsereExercito(Arena *arena, int size, INSTR *p, Time team);
//TEST DONE
void removeExercito(Arena *arena, Time t);

//TEST DONE
void RemoveMortos(Arena *arena, Time t);

Bool hasCrystal(Grid g, int i, int j);

Bool hasEnemy(Grid g, int i, int j, Time friendly);

Bool notOcupied(Grid g, int i, int j);

void inicializaArena(Arena *arena, int nrows, int ncols);

// Funções da struct Maquina

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m, Arena *A);

void exec_maquina(Arena *A, Maquina *m, int n);

OPERANDO sysCall(Arena *A, Maquina *m, OpCode t, Direction op);

OPERANDO moveMachine(Arena *A, Maquina *m, Direction d);

OPERANDO grabCrystal(Arena *A, Maquina *m, Direction d);

OPERANDO depositCrystal(Arena *A, Maquina *m, Direction d);

OPERANDO attackMachine(Arena *A, Maquina *m, Direction d);

void getPosition(Maquina *m, Direction d, int *i, int *j);

#endif