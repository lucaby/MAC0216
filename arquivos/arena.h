#include "maq.h"
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

void inicializaGrid(Arena *arena, int nrows, int ncols);

