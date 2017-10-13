#include "pilha.h"
#include "structures.h"

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
  Cristais crystals;
  bool isDead;
  Team t;
} Maquina;

// Por conta de uma dependência circular entre os headers,
// resolvemos colocar ambas as structs no mesmo header

typedef struct {
  Grid grid;
  int tempo;
  Maquina* exercitos;
  int lastFree;
} Arena;

// Funções da struct Arena

void Atualiza(Arena *arena, int ciclos);

void InsereExercito(Arena *arena, Maquina *exercito);

void RemoveExercito(Arena *arena, Maquina *exercito);

void Sistema(Arena *arena , Maquina* chamador, int op);

void RemoveMortos(Arena *arena, Team t);

bool hasCrystal(Grid g, int i, int j);

bool hasEnemy(Grid g, int i, int j, Team friendly);

bool notOcupied(Grid g, int i, int j);

void inicializaGrid(Arena *arena, int nrows, int ncols);

// Funções da struct Maquina

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Arena *A, Maquina *m, int n);

void sysCall(Arena *A, Maquina *m, OpCode t, Direction op);

void moveMachine(Arena *A, Maquina *m, Direction d);

void grabCrystal(Arena *A, Maquina *m, Direction d);

void depositCrystal(Arena *A, Maquina *m, Direction d);

void attackMachine(Arena *A, Maquina *m, Direction d);

bool hasCrystal(Grid g, int i, int j);

bool hasEnemy(Grid g, int i, int j, Team friendly);

bool notOcupied(Grid g, int i, int j);

void directionsSwitch(Maquina *m, Direction d, int *i, int *j);

#endif