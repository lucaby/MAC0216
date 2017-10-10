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


