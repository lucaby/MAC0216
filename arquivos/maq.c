#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

/* #define DEBUG */

#ifdef DEBUG
#  define D(X) X
char *CODES[] = {
  "PUSH",
  "POP",
  "DUP",
  "ADD",
  "SUB",
  "MUL",
  "DIV",
  "JMP",
  "JIT",
  "JIF",
  "CALL",
  "RET",
  "STS",
  "RCS",
  "EQ",
  "GT",
  "GE",
  "LT",
  "LE",
  "NE",
  "STO",
  "RCL",
  "END",
  "PRN",
  "STL",
  "RCE",
  "ALC",
  "FRE",
  "ATR",
  "MOVE",
  "GRAB",
  "DEPO",
  "ATTK"
};
#else
#  define D(X)
#endif

#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)
#define rbp (m->rbp)
#define x (m->x)
#define y (m->y)

static void Erro(char *msg) {
  fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Maquina *cria_maquina(INSTR *p) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  ip = 0;
  prg = p;
  rbp = 0;
  x = 0;
  y = 0;
  m->crystals = 0;
  return m;
}

void destroi_maquina(Maquina *m, Arena *A) {
  free(m);
  free(A);
}

/* Novas funções para as chamadas de sistema */

void directionsSwitch(Maquina *m, Direction d, int *i, int *j) {
	switch(d) {
		case WEST:
			*i = x - 2;
			*j = y;
			break;
		case NWEST:
			*i = x - 1;
			*j = y - 1;
			break;
		case NEAST:
			*i = x + 1;
			*j = y - 1;
			break;
		case EAST:
			*i = x + 2;
			*j = y;
			break;
		case SEAST:
			*i = x + 1;
			*j = y + 1;
			break;
		case SWEST:
			*i = x - 1;
			*j = y + 1;
			break;
	}
}

void moveMachine(Arena *A, Maquina *m, Direction d){
	int i, j;
	directionsSwitch(m, d, &i, &j);
	if(notOcupied(A->grid, i, j)){
		x += i;
		y += j;
	}
}

void grabCrystal(Arena *A, Maquina *m, Direction d){
	int i, j;
	directionsSwitch(m, d, &i, &j);
	if(hasCrystal(A->grid, i, j)) {
		A->grid[i][j].c--;
		(m->crystals)++;
	}
}

void depositCrystal(Arena *A, Maquina *m, Direction d) {
	int i, j;
	directionsSwitch(m, d, &i, &j);
	A->grid[i][j].c++;
}

void attackMachine(Arena *A, Maquina *m, Direction d) {
	int i, j;
	directionsSwitch(m, d, &i, &j);
	if(hasEnemy)
		printf("EXTERMINATE!");
}


void sysCall(Arena *A, Maquina *m, OpCode t, Direction op){
	switch(t) {
		case MOVE:
			moveMachine(A, m, op);
			break;
		case GRAB:
			grabCrystal(A, m, op);
			break;
		case DEPO:
			depositCrystal(A, m, op);
			break;
		case ATTK:
			attackMachine(A, m, op);
			break;
	}
}

void exec_maquina(Arena *A, Maquina *m, int n) {
  int i;
  exec->topo = 0;
  pil->topo = 0;
  for (i = 0; i < n; i++) {
	Tipo    tipo = prg[ip].t;
	OpCode   opc = prg[ip].instr;
	OPERANDO arg = prg[ip].op;
  	/* printf("i: %d\n opc: %d\n arg: %u\n", i, opc, arg); */

	D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg.n));
		switch(tipo) {

			case NUM:
				switch (opc) {
					  OPERANDO tmp;
					case PUSH:
					  empilha(pil, arg);
					  break;
					case POP:
					  desempilha(pil).n;
					  break;
					case DUP:
					  tmp = desempilha(pil);
					  empilha(pil, tmp);
					  empilha(pil, tmp);
					  break;
					case ADD:
						tmp.n = desempilha(pil).n + desempilha(pil).n;
					  	empilha(pil, tmp);
					  break;
					case SUB:
					  tmp.n = desempilha(pil).n;
					  tmp.n = desempilha(pil).n - tmp.n;
					  empilha(pil, tmp);
					  break;
					case MUL:
					  tmp.n = (desempilha(pil).n)*(desempilha(pil).n);
					  empilha(pil, tmp);
					  break;
					case DIV:
					  tmp.n = desempilha(pil).n;
					  tmp.n = desempilha(pil).n/tmp.n;
					  empilha(pil, tmp);
					  break;
					case JMP:
					  ip = arg.n;
					  continue;
					case JIT:
					  if (desempilha(pil).n != 0) {
						ip = arg.n;
						continue;
					  }
					  break;
					case JIF:
					  if (desempilha(pil).n == 0) {
						ip = arg.n;
						continue;
					  }
					  break;
					// Insiro o rbp na pilha de execução logo antes do ip
					case CALL:
						tmp.n = ip;
					  	empilha(exec, tmp);
					  	tmp.n = rbp;
					  	empilha(exec, tmp);
					  	rbp = exec->topo;
					  	ip = arg.n;
					  continue;
					case RET:
					// Usuário deve dar FRE antes de chamar RET neste caso
					  rbp = desempilha(exec).n;
					  ip = desempilha(exec).n;
					  break;
					case EQ:
					  	if (desempilha(pil).n == desempilha(pil).n) {
					  		tmp.n = 1;
							empilha(pil, tmp);
						}
					  	else {
					  		tmp.n = 0;
							empilha(pil, tmp);
						}
					  break;
					case GT:
					  	if (desempilha(pil).n < desempilha(pil).n) {
							tmp.n = 1;
							empilha(pil, tmp);
						}
					  else {
					  		tmp.n = 0;
							empilha(pil, tmp);
						}
					  break;
					case GE:
					  	if (desempilha(pil).n <= desempilha(pil).n) {
							tmp.n = 1;
							empilha(pil, tmp);
						}
					 	else {
							tmp.n = 0;
							empilha(pil, tmp);
						}
					  break;
					case LT:
					  	if (desempilha(pil).n > desempilha(pil).n) {
							tmp.n = 1;
							empilha(pil, tmp);
						}
					  else {
					  	tmp.n = 0;
						empilha(pil, tmp);
					}
					  break;
					case LE:
					  	if (desempilha(pil).n >= desempilha(pil).n) {
							tmp.n = 1;
							empilha(pil, tmp);
						}
					  	else {
							tmp.n = 1;
							empilha(pil, tmp);
						}
					  break;
					case NE:
					  	if (desempilha(pil).n != desempilha(pil).n) {
							tmp.n = 1;
							empilha(pil, tmp);
						}
					  	else {
						  	tmp.n = 0;
							empilha(pil, tmp);
						}
					  break;
					case STO:

					  m->Mem[arg.n] = desempilha(pil);
					  break;
					case RCL:
					  empilha(pil,m->Mem[arg.n]);
					  break;
					case END:
					  return;
					case PRN:
					  printf("%d\n", desempilha(pil).n);
					  break;
					// Casos adicionados 
					case STL:
					  tmp.n = desempilha(pil).n;
					  exec->val[rbp + arg.n] = tmp;
					  break;
					case RCE:
					  tmp = exec->val[rbp + arg.n];
					  empilha(pil, tmp);
					  break;
					case ALC:
					// Salvar o valor da memória que foi armazenada para que ela seja liberada depois
				      exec->topo += arg.n;
				      empilha(exec, arg);
					  break;
					case FRE:
					// Test implementation
					  exec->topo -= desempilha(exec).n;
					  break;

					// A partir daqui implementamos as coisas para a Fase II
					case ATR:
						tmp = desempilha(pil);
						empilha(pil, tmp);
						break;
				}
				break;
			case ACAO:

				sysCall(A, m, opc, arg.d);
				break;
			
			case VAR:

				break;
				
	}
	D(imprime(pil,5));
	D(puts("\n"));

	ip++;
  }
}


void InsereExercito(Arena *arena, int size, INSTR *p, int time) {
	printf("Dalek built!: %d", arena->lastFree);
	int i = arena->lastFree;
	int n = i + size;
	while(n < 100 && i < n){
		Maquina *robo;
		robo = cria_maquina(p);
		robo->t = time;
		arena->exercitos[i] = robo;
		arena->lastFree++;
		i++;
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
   		if(arena->exercitos[i] != NULL)
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

















