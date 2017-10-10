#include "maq.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	Grid grid;
	int tempo;
	Maquina*[100] exercitos;
	int lastFree;
} Arena;

void Atualiza(Arena *arena, int ciclos);

void InsereExercito(Arena *arena, Maquina *exercito);

void RemoveExercito(Arena *arena, Maquina *exercito);

void Sistema(Arena *arena , Maquina* chamador, int op);

int partition( Maquina*[], int l, int r);