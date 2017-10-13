
#ifndef MAQ_H
#define MAQ_H


#include "pilha.h"
#include "structures.h"
#include "instr.h"

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
  Grid grid;
  int tempo;
  Maquina* exercitos[MAXMEM];
  int lastFree;
} Arena;

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