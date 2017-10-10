void InsereExercito(Arena *arena, Maquina *exercito) {
	arena->exercitos[(arena->lastFree)++] = exercito;
}
//Implement quicksort partition.
void RemoveExercito(Arena *arena, Maquina *exercito) {

	
}	

int partition( Maquina*[], int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( a[i] <= pivot && i <= r );
   	do --j; while( a[j] > pivot );
   	if( i >= j ) break;
   	t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
} 