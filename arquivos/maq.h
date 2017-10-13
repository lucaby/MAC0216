#include "pilha.h"
#include "structures.h"
#include "arena.h"
#include "instr.h"

#ifndef MAQ_H
#define MAQ_H

#define MAXMEM 100

typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip;
  int rbp;
  int x;
  int y;
  int crystals;
  bool isDead;
  Time t;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);

void sysCall(Maquina *m, Tipo t, OPERANDO op);

void moveMachine(Arena *A, Maquina *m, Directions d);

void grabCrystal(Arena *A, Maquina *m, Directions d);

void depositCrystal(Arena *A, Maquina *m, Directions d);

void attackMachine(Arena *A, Maquina *m, Directions d);

bool hasCrystal(Grid g, int i, int j);

bool hasEnemy(Grid g, int i, int j, Team friendly);

bool notOcupied(Grid g, int i, int j);

void directionsSwitch(Maquina *m, Directions d, int *i, int *j);

#endif