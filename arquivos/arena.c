void InsereExercito(Arena *arena, Maquina *exercito) {
	arena->exercitos[(arena->lastFree)++] = exercito;
}
//Implement quicksort partition.
void RemoveExercito(Arena *arena, Maquina *exercito) {

	
}	

void Atualiza(Arena *arena, int ciclos) {
   for(int i = 0; i < 100; ++i) {
      exec_maquina(arena->exercitos[i], ciclos);
   }
   arena->tempo += 1;
}


void inicializaGrid(Arena *arena, int nrows, int ncols) {
	arena->grid = malloc(nrows * sizeof(Grid *));
	for(int i = 0; i < nrows; i++) {
	    arena->grid[i] = malloc(ncolumns * sizeof(Grid));
	    if(arena->exercitos[i] == NULL) {
	        fprintf(stderr, "out of memory\n");
	        exit or return
	    }
	}
	for(int j = 0; j < nrows; j++) {
		if (j % 2 == 0) {
			for(int i = 1; i < ncols; i += 2) {
				arena->grid[i][j].o = false;
				arena->grid[i][j].n = i+j;
			}
		}
		else {
			for(int i = 0; i < ncols; i += 2) {
				arena->grid[i][j].o = false;
				arena->grid[i][j].n = i+j;
				
				//TODO: inicializar as outras coisas
				//arena->exercitos[i][j].base
				//arena->exercitos[i][j].

			}
		}
	}
}

