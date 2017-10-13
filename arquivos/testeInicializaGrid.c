#include "maq.h"

int main() {
	Arena *a;
	inicializaArena(a, 10, 10);
	int nrows = 10;
	int ncols = 10;

		for(int j = 0; j < nrows; j++) {
			for(int i = 0; i < ncols; i++) {
				printf("%d ", a->grid[i][j].o.ocupado);
			}
		printf("\n");
	}
	return 0;

}