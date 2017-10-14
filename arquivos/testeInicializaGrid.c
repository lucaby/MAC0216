#include "maq.h"
#include <stdio.h>
int main() {
	Arena *a = malloc(sizeof(Arena *));
	inicializaArena(a, 10, 10);
	int nrows = 10;
	int ncols = 10;

	printf("Cristal positions: \n");
	for(int j = 0; j < nrows; j++) {
			if (j % 2 == 0) {
				for(int i = 0; i < ncols; i += 1) {
					if((i % 2 == 0))
						printf("X ");
					else {
						printf("%d ", a->grid[i][j].c);
					}
				}
			}
			else {
				for(int i = 0; i < ncols; i += 1) {
					if((i % 2 == 1))
						printf("X ");
					else {
						printf("%d ", a->grid[i][j].c);
					}
				}
			}
			printf("\n");
	}

	printf("Bases: \n");

		for(int j = 0; j < nrows; j++) {
			if (j % 2 == 0) {
				for(int i = 0; i < ncols; i += 1) {
					if((i % 2 == 0))
						printf("X ");
					else {
						printf("%d ", a->grid[i][j].b.isBase);

						
					}
				}
			}
			else {
				for(int i = 0; i < ncols; i += 1) {
					if((i % 2 == 1))
						printf("X ");
					else {
						printf("%d ", a->grid[i][j].b.isBase);						
					}
				}
			}
			printf("\n");
		}
	return 0;
}

