#include "arena.h"
#include <stdio.h>
void inicializaArena(Arena *arena, int nrows, int ncols) {
	arena->tempo = 0;
	arena->lastFree = 0;
	
	arena->grid = malloc(nrows * sizeof(Celula *));
	for(int i = 0; i < nrows; i++) {
	    arena->grid[i] = (Celula *) malloc(ncols * sizeof(Celula));
	}
	for(int j = 0; j < nrows; j++) {
		if (j % 2 == 0) {
			for(int i = 1; i < ncols; i += 2) {
				arena->grid[i][j].o.ocupado = True;
			}			
		}

		
		else {
			for(int i = 0; i < ncols; i += 2) {
				arena->grid[i][j].o.ocupado = True;
				
				//TODO: inicializar as outras coisas
				//arena->exercitos[i][j].base
				//arena->exercitos[i][j].

			}
		}
	}
}

  void InsereExercito(Arena *arena, int size, INSTR *p, int time) {	
	for(int i = arena->lastFree; i < 100; i++){
		Maquina *robo;
		
		robo = cria_maquina(p);
		robo->t = time;
		arena->exercitos[i] = robo;
	}

	if(size > 100-arena->lastFree) printf("The Arena is full.\n"); 
}


//Implement quicksort partition. Assim nao precisamos nos preocupar em retirar os robos
void RemoveExercito(Arena *arena,Time t) {
	for(int i = 99; i >=0; i--) {
		if(arena->exercitos[i] != NULL && arena->exercitos[i]->t == t) {
			arena->exercitos[i] = NULL;
		}
	}

	
}	

void Atualiza(Arena *arena, int ciclos) {
   for(int i = 0; i < arena->lastFree; ++i) {
      exec_maquina(arena, arena->exercitos[i], ciclos);
   }
   arena->tempo += 1;
}

void RemoveMortos(Arena *arena, Time t) {
	for(int i = 99; i >=0; i--) {
		if(arena->exercitos[i] != NULL && arena->exercitos[i]->isDead) {
			arena->exercitos[i] = NULL;
		}
	}
}

Bool hasCrystal(Grid g, int i, int j) {
	return (g[i][j].c > 0);
}

Bool hasEnemy(Grid g, int i, int j, Time friendly) {
	if(g[i][j].o.ocupado && g[i][j].o.time != friendly)
		return True;
	return False;
}


Bool notOcupied(Grid g, int i, int j) {
	return !g[i][j].o.ocupado;
}



