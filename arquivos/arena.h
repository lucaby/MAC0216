#ifndef ARENA_H
#define ARENA_H

#include "pilha.h"
#include "structures.h"
#include "instr.h"
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
  Bool isDead;
  Time t;
} Maquina;

typedef struct {
  Celula** grid;
  int tempo;
  Maquina* exercitos[MAXMEM];
  int lastFree;
} Arena;


void Atualiza(Arena *arena, int ciclos);

void InsereExercito(Arena *arena, int size, INSTR *p, int time);

void RemoveExercito(Arena *arena, Time t);

void Sistema(Arena *arena , Maquina* chamador, int op);

void RemoveMortos(Arena *arena, Time t);

Bool hasCrystal(Grid g, int i, int j);

Bool hasEnemy(Grid g, int i, int j, Time friendly);

Bool notOcupied(Grid g, int i, int j);

void inicializaArena(Arena *arena, int nrows, int ncols);

// Funções da struct Maquina

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m, Arena *A);

void exec_maquina(Arena *A, Maquina *m, int n);

void sysCall(Arena *A, Maquina *m, OpCode t, Direction op);

void moveMachine(Arena *A, Maquina *m, Direction d);

void grabCrystal(Arena *A, Maquina *m, Direction d);

void depositCrystal(Arena *A, Maquina *m, Direction d);

void attackMachine(Arena *A, Maquina *m, Direction d);

void directionsSwitch(Maquina *m, Direction d, int *i, int *j);

#endif