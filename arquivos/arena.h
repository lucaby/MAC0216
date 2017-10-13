#ifndef ARENA_H
#define ARENA_H

#include "instr.h"
#include "structures.h"
#include "maq.h"

void Atualiza(Arena *arena, int ciclos);

void InsereExercito(Arena *arena, int size, INSTR *p, int time);

void RemoveExercito(Arena *arena, Time t);

void Sistema(Arena *arena , Maquina* chamador, int op);

void RemoveMortos(Arena *arena, Time t);

Bool hasCrystal(Grid g, int i, int j);

Bool hasEnemy(Grid g, int i, int j, Time friendly);

Bool notOcupied(Grid g, int i, int j);

void inicializaArena(Arena *arena, int nrows, int ncols);

#endif