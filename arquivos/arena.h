#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "maq.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	Grid grid;
	int tempo;
	Maquina* exercitos;
	int lastFree;
} Arena;

void Atualiza(Arena *arena, int ciclos);

void InsereExercito(Arena *arena, Maquina *exercito);

void RemoveExercito(Arena *arena, Maquina *exercito);

void Sistema(Arena *arena , Maquina* chamador, int op);


void RemoveMortos(Arena *arena, Time t);

bool hasCrystal(Grid g, int i, int j);

bool hasEnemy(Grid g, int i, int j, Team friendly);

bool notOcupied(Grid g,Grid g, int i, int j);

void inicializaGrid(Arena *arena, int nrows, int ncols);


#endif