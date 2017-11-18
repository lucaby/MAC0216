#include "arena.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

FILE *display;
//nrows = 2 * ncols
void inicializaArena(Arena *arena, int nrows, int ncols) {
	/*(arena, #linhas, #coluna) -> void
	Aloca dinamicamente uma matrix de células de tamanho nrowsxncols.
	Para fins de simplicidade incializamos "aleatoriamente" algumas
	células com cristais. Além disso, colocamos bases dos times, além de
	indicar que as células estão desocupadas. Esta função deve sempre ser
	chamada no início do jogo.*/
	
	display = popen("python3 apres", "w");

	arena->rows = nrows;
	arena->cols = ncols;
	arena->tempo = 0;
	arena->firstFree = 0;
	srand(time(NULL));

	arena->grid = (Celula **) malloc(sizeof(Celula *) * ncols);
	int i;
	for(i = 0; i < ncols; i++) {
	    arena->grid[i] = (Celula *) malloc(sizeof(Celula) * nrows);
	}


	for(int j = 0; j < nrows; j++) {
		if (j % 2 == 1) {
			for(int i = 1; i < ncols; i += 2) {
				arena->grid[i][j].o.ocupado = False;
				//Gera o terreno da case (i,j). Implementacao bem simples sem agrupamento
				arena->grid[i][j].t = rand() % 5;
				arena->grid[i][j].b.isBase = False;
				arena->grid[i][j].c = False;
				//Sets the bases
				fprintf(display, "terr %d %d %d\n", j, i / 2 , (int)arena->grid[i][j].t);
			}
		}	
		else {
			for(int i = 0; i < ncols; i += 2) {
				arena->grid[i][j].o.ocupado = False;
				//Gera o terreno da case (i,j). Implementacao bem simples sem agrupamento
				arena->grid[i][j].t = rand() % 5;
				arena->grid[i][j].b.isBase = False;
				arena->grid[i][j].c = False;
				fprintf(display, "terr %d %d %d\n", j, i / 2, (int)arena->grid[i][j].t);
				//Sets the bases

			}
		}
	}


	arena->grid[0][0].b.isBase = True;
	arena->grid[0][0].b.team = RED;
	fprintf(display, "home ./sprites/homeRed.png %d %d \n", 0, 0);
	arena->grid[nrows-1][ncols-1].b.isBase = True;
	arena->grid[nrows-1][ncols-1].b.team = BLUE;
	fprintf(display, "home ./sprites/homeRed.png %d %d \n", nrows-1, ncols-1);	
	fprintf(display, "init\n");

	for(int i = 0; i <= ncols / 2;) {
		
		int r1 = rand() % nrows;
		int r2 = (rand() % ncols);
		if((r1 % 2 == 0 && r2 % 2 == 0) || (r1 % 2 == 1 && r2 % 2 == 1) && arena->grid[r1][r2].o.ocupado == False) {
			arena->grid[r1][r2].c = True;
			arena->grid[r1][r2].o.ocupado = True;
			fprintf(display, "crys ./sprites/crystal.png %d %d\n", r1 , r2 / 2);

			i++;
		}
	}
	
}


void InsereExercito(Arena *arena, int size, INSTR *p, Time team) {
  	/*(arena, size, instruções, time) -> void
  	Insere no vetor de máquinas da Arena uma quantidade size de robôs de um time team*/
  	

	int x = 1;
	int k;
  	if(size > 100-arena->firstFree) {
  		printf("The Arena is full.\n");
  		return;
  	}

  	if(team == BLUE) {
  		k = 1;
  	}
  	else {
  		k = arena->rows - 2;
  	}
  	if(k % 2 == 0) {
  		x = 2;
  	}
 
	for(int i = arena->firstFree; i < size + arena->firstFree; i++){
				
		if(team == BLUE) {
			fprintf(display, "rob ./sprites/roboBlue.png\n");
		}
		else {
			fprintf(display, "rob ./sprites/roboRed.png\n");
		}
		Maquina *robo;
		robo = cria_maquina(p, 0, 0);
		robo->t = team;
		robo->crystals = 0;
		robo->alive = True;
		robo->x = robo->oldX = x;
		robo->y = robo->oldY = k;
		robo->hp = 100;
		robo->damage = 10;
		robo->defense = 2;
		x += 2;
		if(i == 0)
			robo->id = 0;
		else
			robo->id = ++(arena->exercitos[i-1]->id);
		
		printRobot(robo);
		
		arena->exercitos[i] = robo;
		arena->grid[k][x].o.ocupado = True;
		arena->grid[k][x].o.team = team;
		arena->grid[k][x].o.id = robo->id;

	}

	arena->firstFree += size;
}

void printRobot(Maquina* maq) {
	int i, j;
	i = maq->y;
	j = maq->x / 2;
	
	fprintf(display, "%d %d %d %d %d\n",
						maq->id, maq->oldY, maq->oldX / 2, i, j);
	fflush(display);
	sleep(2);
}

void closeArena(Arena *arena){
	pclose(display);
}


void Atualiza(Arena *arena, int ciclos) {
	/*(arena, ciclos) -> 
	Executa, dado um time t, um número ciclos de vezes o vetor de instruções dos
	robôs daquele time.*/
    
    for(int i = 0; i < arena->firstFree; ++i) {
    	if (arena->exercitos[i]->time == 0) {
      		exec_maquina(arena, arena->exercitos[i], ciclos);
    	}
    	else arena->exercitos[i]->time--;
    }
    arena->tempo += 1;
}

int tapaBuraco(Maquina* m[], int firstFree) {
	int i = -1, j = firstFree+1;
	while(1) {
		while(m[++i] != NULL);
		while(m[--j] == NULL);
		if(j < i ) break;
		Maquina* tmp = m[i];
		m[i] = m[j];
		m[j] = tmp;
	}
	if(j < 0)
		j = 0;
	else
		j++;
	return j;
}

void RemoveMortos(Arena *arena, Time t) {
	/*(arena, time) -> 
	Remove, dado um time t, do vetor de máquinas da arena, apenas aqueles que
	estão mortos. Ou seja, sua variável alive == true.*/
	
	for(int i = 0; i < arena->firstFree; i++) {
		if(arena->exercitos[i] != NULL && !arena->exercitos[i]->alive) {
			
			arena->exercitos[i] = NULL;
		}
	}
	arena->firstFree = tapaBuraco(arena->exercitos, arena->firstFree);
}

void removeExercito(Arena *arena, Time t) {
	/*(arena, time) -> void
	Dado um time t, descarta todos os robôs daquele time no vetor de máquinas da arena.
	Depois reoganiza os robôs para liberar espaço no vetor de robôs.*/

	for(int i = 0; i < arena->firstFree; i++) {
		if(arena->exercitos[i] != NULL && arena->exercitos[i]->t == t) {
			arena->exercitos[i] = NULL;
		}
	}


	arena->firstFree = tapaBuraco(arena->exercitos, arena->firstFree);
}	

// Funções simples para uma leitura melhor de funções anteriores
// Em especial as chamadas de sistema

Bool hasCrystal(Grid g, int i, int j) {
	return (g[i][j].c == True);
}

Bool hasEnemy(Grid g, int i, int j, Time friendly) {
	if(g[i][j].o.ocupado && g[i][j].o.team != friendly)
		return True;
	return False;
}


Bool occupied(Grid g, int i, int j) {
	return g[i][j].o.ocupado;
}


void getPosition(Maquina *m, Direction d, int *i, int *j, int rows, int cols) {
	/* (maquina, direção, i, j) -> null
	Dada uma Maquina m na posição (x,y), inserimos em i e j a 
	posição correspondente a direção que o usuário chamou o sistema
	para efetuar a ação. Para controlar as posições inválidas nas bordas
	da arena, atribuímos um valor à i e j antes de começar e testamos as seguintes
	condĩções: */
	switch(d) {
		case WEST:
			if(m->x > 1){
				*j = m->x - 2;
				*i = m->y;
			}
			break;
		case NWEST:
			if(m->x > 0 && m->y > 0){
				*j = m->x - 1;
				*i = m->y - 1;
			}
			break;
		case NEAST:
			if(m->x < cols - 1 && m->y > 0){
				*j = m->x + 1;
				*i = m->y - 1;
			}
			break;
		case EAST:
			if(m->x < cols - 2){
				*j = m->x + 2;
				*i = m->y;
			}
			break;
		case SEAST:
			if(m->x < cols - 1 && m->y < rows - 1){
				*j = m->x + 1;
				*i = m->y + 1;
			}
			break;
		case SWEST:
			if(m->x > 0 && m->y < rows - 1) {
				printf("entrei no SWEST!\n");
				*j = m->x - 1;
				*i = m->y + 1;
			}
			break;
	}
}

OPERANDO moveMachine(Arena *arena, Maquina *m, Direction d){
	/*(arena, maquina, direção) -> operando (true or false)
	Quando o usuário chama o sistema para efetuar um movimento
	esta função verifica se a posição requerida está livre para a ação
	e muda a posição do robô em caso afirmativo. Devolve um operando 
	tal qual sua parte inteira indica se a ação conseguiu ser realizada ou não.*/
	int i = -1, j = -1;
	OPERANDO result;
	result.n = False;
	getPosition(m, d, &i, &j, arena->rows, arena->cols);
	
	if(i != -1 && !occupied(arena->grid, i, j)) {
		m->oldY = m->y;
		m->oldX = m->x;
		arena->grid[m->oldY][m->oldX].o.ocupado = False;
		arena->grid[m->oldY][m->oldX].o.id = -1;
		arena->grid[i][j].o.ocupado = True;
		arena->grid[i][j].o.team = m->t;
		m->x = j;
		m->y = i;
		arena->grid[i][j].o.id = m->id;
		result.n = True;
		printRobot(m);
	}
	

	switch(arena->grid[i][j].t) {
		case ESTRADA:
			break;
		case RIO:
			m->time += 2;
			break;		
		case MONTANHA:
			m->time += 5;
			break;
		case LAMA:
			m->time += 4;
			break;
		case CAMPO: 
			m->time += 1;
			break;
	}

	return result;
}

OPERANDO grabCrystal(Arena *arena, Maquina *m, Direction d){
	/*(arena, maquina, direção) -> operando (true or false)
	Quando o usuário chama o sistema para pegar um cristal que está na
	posição referente a direção d, esta função verifica se há cristais
	na posição e atualiza a quantidade de cristais do robô e do local caso
	afirmativo. Devolve um operando que tem a  parte inteira indicando
	se a ação conseguiu ser realizada ou não.*/
	int i = -1, j = -1;
	OPERANDO result;
	result.n = False;
	getPosition(m, d, &i, &j, arena->rows, arena->cols);

	if(i != -1 && hasCrystal(arena->grid, i, j)) {
		printf("quase peguei cristal\n");
		arena->grid[i][j].c--;
		(m->crystals)++;
		result.n = True;
		arena->grid[i][j].o.ocupado = False;
		fprintf(display, "remCrys %d %d \n", i, j / 2);
	}
	m->time++;
	return result;
}

OPERANDO depositCrystal(Arena *arena, Maquina *m, Direction d) {
	/*(arena, maquina, direção) -> operando (true or false)
	Neste caso, dada a chamada de sistema para depositar um cristal numa 
	direção d, é verificado se o robô possui algum cristal. Caso tenha, atualizamos
	a quantidade de cristais do robô e da posição do grid onde foi depositado.
	Devolvemos um OPERANDO indicando se a operação foi bem sucedida.*/
	int i = -1, j = -1;
	OPERANDO result;
	result.n = False;
	getPosition(m, d, &i, &j, arena->rows, arena->cols);
	if(i != -1 && m->crystals > 0){
		arena->grid[i][j].c++;
		m->crystals--;
		result.n = True;
		arena->grid[i][j].o.ocupado = True;
		fprintf(display, "crys ./sprites/crystal.png %d %d\n", i , j / 2);
	}
	m->time++;
	return result;
}

OPERANDO attackMachine(Arena *arena, Maquina *m, Direction d) {
	/*(arena, maquina, direção) -> operando (true or false)
	Por simplicidade quanto ao sistema de hit points dos robôs, seus respectivos
	pontos de ataque e defesa, apenas imprimimos uma mensagem na saída padrão
	indicando que o ataque foi realizado. Devolvemos também a indicação desse resultado.*/
	int i = -1, j = -1;
	OPERANDO result;
	result.n = False;
	getPosition(m, d, &i, &j, arena->rows, arena->cols);
	if(i != -1 && hasEnemy(arena->grid, i, j, m->t)){
		int enemy = getEnemy(arena, i, j);
		int damage = getDamage(m);
		printf("EXTERMINATE!\n");
		arena->exercitos[enemy]->hp -= damage - arena->exercitos[enemy]->defense;
		
		if(arena->exercitos[enemy]->hp < 0){
			fprintf(display, "die %d %d\n", i, (j/2));
			arena->grid[i][j].o.ocupado = False;
			arena->grid[i][j].o.id = -1;
		}

		printf("hp after: %d\n", arena->exercitos[enemy]->hp);
		result.n = True;
	}
	return result;
}

OPERANDO sysCall(Arena *arena, Maquina *m, OpCode t, Direction op){
	/*(arena, maquina, ação, direção) -> operando (true or false)
	Apenas delega, dependendo da ação (OpCode t) qual das funções
	devem ser chamadas e retorna o resultado.*/
	OPERANDO result;
	//if(m->time == 0) 
		switch(t) {
			case MOVE:
				result = moveMachine(arena, m, op);
				break;
			case GRAB:
				result = grabCrystal(arena, m, op);
				break;
			case DEPO:
				result = depositCrystal(arena, m, op);
				break;
			case ATTK:
				result = attackMachine(arena, m, op);
				break;

	}
	//else m->time--;

	return result;
}

int getEnemy(Arena *arena, int lin, int col){
	int i = 0;
	int id = arena->grid[lin][col].o.id;

	while(i < arena->firstFree && arena->exercitos[i]->id != id)
		i++;

	return i;
}

int getDamage(Maquina *m){
	srand(time(NULL));
	int damage = m->damage + rand()%10;
	if(m->hp < 50 && m->hp > 20)
		damage = damage/2;
	else if(m->hp< 20)
		damage = damage/3;
	return damage;
}