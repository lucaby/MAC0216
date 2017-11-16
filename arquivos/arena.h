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
	int oldX;
	int oldY;
	int hp;
	Cristais crystals;
	Bool alive;
	Time t;
	int time;
} Maquina;

typedef struct {
	Grid grid;
	int rows;
	int cols;
	int tempo;
	Maquina* exercitos[MAXMEM];
	int firstFree;
} Arena;

//TEST DONE
void Atualiza(Arena *arena, int ciclos);

//TEST DONE
int tapaBuraco(Maquina* m[],int firstFree);

//TEST DONE
void InsereExercito(Arena *arena, int size, INSTR *p, Time team);

//TEST DONE
void removeExercito(Arena *arena, Time t);

//TEST DONE
void RemoveMortos(Arena *arena, Time t);

//TEST DONE
Bool hasCrystal(Grid g, int i, int j);

//TEST NEEDED
Bool hasEnemy(Grid g, int i, int j, Time friendly);

//TEST NEEDED
Bool occupied(Grid g, int i, int j);

//TEST DONE
void inicializaArena(Arena *arena, int nrows, int ncols);

// Funções da struct Maquina

Maquina *cria_maquina(INSTR *p, int x, int y);

void destroi_maquina(Maquina *m, Arena *A);

void exec_maquina(Arena *A, Maquina *m, int n);

//TEST DONE
OPERANDO sysCall(Arena *A, Maquina *m, OpCode t, Direction op);

// TEST DONE
OPERANDO moveMachine(Arena *A, Maquina *m, Direction d);

//TEST DONE
OPERANDO grabCrystal(Arena *A, Maquina *m, Direction d);

//TEST DONE
OPERANDO depositCrystal(Arena *A, Maquina *m, Direction d);

//TEST DONE
OPERANDO attackMachine(Arena *A, Maquina *m, Direction d);

//TEST IN PROGRESS
void  getPosition(Maquina *m, Direction d, int *i, int *j, int rows, int cols);

#endif