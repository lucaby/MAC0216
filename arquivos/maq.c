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
  "FRE"
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
#define crystals (m->crystals)
#define grid (arena->grid->grid)
#define Direction (OPERANDO.direction)

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
  crystals = 0;
  return m;
}

void destroi_maquina(Maquina *m) {
  free(m);
}

/* Alguns macros para facilitar a leitura do código */

void exec_maquina(Maquina *m, int n) {
  int i;
  exec->topo = 0;
  pil->topo = 0;
  for (i = 0; i < n; i++) {
	OpCode   opc = prg[ip].instr;
	Tipo    tipo = prg[ip].t;
	OPERANDO arg = prg[ip].op;
  	/* printf("i: %d\n opc: %d\n arg: %u\n", i, opc, arg); */

	D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg.n));
		switch(tipo) {

			case NUM:
				switch (opc) {
					  OPERANDO tmp;
					case PUSH:
					  empilha(pil, arg.n);
					  break;
					case POP:
					  desempilha(pil);
					  break;
					case DUP:
					  tmp = desempilha(pil);
					  empilha(pil, tmp);
					  empilha(pil, tmp);
					  break;
					case ADD:
					  empilha(pil, desempilha(pil)+desempilha(pil));
					  break;
					case SUB:
					  tmp = desempilha(pil);
					  empilha(pil, desempilha(pil)-tmp);
					  break;
					case MUL:
					  empilha(pil, desempilha(pil)*desempilha(pil));
					  break;
					case DIV:
					  tmp = desempilha(pil);
					  empilha(pil, desempilha(pil)/tmp);
					  break;
					case JMP:
					  ip = arg.n;
					  continue;
					case JIT:
					  if (desempilha(pil) != 0) {
						ip = arg.n;
						continue;
					  }
					  break;
					case JIF:
					  if (desempilha(pil) == 0) {
						ip = ar.n;
						continue;
					  }
					  break;
					// Insiro o rbp na pilha de execução logo antes do ip
					case CALL:
					  empilha(exec, ip);
					  empilha(exec, rbp);
					  rbp = exec->topo;
					  ip = arg.n;
					  continue;
					case RET:
					// Usuário deve dar FRE antes de chamar RET neste caso
					  rbp = desempilha(exec);
					  ip = desempilha(exec);
					  break;
					case EQ:
					  if (desempilha(pil) == desempilha(pil))
						empilha(pil, 1);
					  else
						empilha(pil, 0);
					  break;
					case GT:
					  if (desempilha(pil) < desempilha(pil))
						empilha(pil, 1);
					  else
						empilha(pil, 0);
					  break;
					case GE:
					  if (desempilha(pil) <= desempilha(pil))
						empilha(pil, 1);
					  else
						empilha(pil, 0);
					  break;
					case LT:
					  if (desempilha(pil) > desempilha(pil))
						empilha(pil, 1);
					  else
						empilha(pil, 0);
					  break;
					case LE:
					  if (desempilha(pil) >= desempilha(pil))
						empilha(pil, 1);
					  else
						empilha(pil, 0);
					  break;
					case NE:
					  if (desempilha(pil) != desempilha(pil))
						empilha(pil, 1);
					  else
						empilha(pil, 0);
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
					  printf("%d\n", desempilha(pil));
					  break;
					// Casos adicionados 
					case STL:
					  tmp = desempilha(pil);
					  exec->val[rbp + arg.n] = tmp;
					  break;
					case RCE:
					  tmp = exec->val[rbp + arg.n];
					  empilha(pil, tmp);
					  break;
					case ALC:
					// Salvar o valor da memória que foi armazenada para que ela seja liberada depois
				      exec->topo += arg.n;
				      empilha(exec, arg.n);
					  break;
					case FRE:
					// Test implementation
					  exec->topo -= desempilha(exec);
					  break;

					// A partir daqui implementamos as coisas para a Fase II
					case ATR:
						tmp = desempilha(pil);
						empilha(pil, tmp.arg.n);
						break;
				}
				break;
			case ACAO:

				sysCall(m, opc, arg.d);
				break;
			
			case VAR:

				break;
				
	}
	D(imprime(pil,5));
	D(puts("\n"));

	ip++;
  }

void sysCall(Maquina *m, OpCode t, direction op){
	switch(t) {
		case MOVE:
			moveMachine(m, op);
			break;
		case GRAB:
			grabCrystal(m, op);
			break;
		case DEPO:
			depositCrystal(m, op);
			break;
		case ATTK:
			attackMachine(m, op);
			break;
	}
}

void moveMachine(Arena *A, Maquina *m, DIrection d){
	int i, j;
	directionsSwitch(m, d, &i, &j);
	if(notOcupied(grid, i, j)){
		x += i;
		y += j;
	}
}

void grabCrystal(Arena *A, Maquina *m, Direction d){
	int i, j;
	directionsSwitch(m, d, &i, &j);
	if(hasCrystal(grid, i, j)){
		grid[i][j]--;
		m->crytals++;
	}
}

void depositCrystal(Arena *A, Maquina *m, Direction d) {
	int i, j;
	directionsSwitch(m, d, &i, &j);
	grid[i][j]++;
}

void attackMachine(Arena *A, Maquina *m, Direction d){
	int i, j;
	directionsSwitch(m, d, &i, &j);
	if(hasEnemy)
		printf("EXTERMINATE!");
}

void directionsSwitch(Maquina *m, Direction d, int *i, int *j){
	switch(d) {
		case W:
			*i = x - 2;
			*j = y;
			break;
		case NW:
			*i = x - 1;
			*j = y - 1;
			break;
		case NE:
			*i = x + 1;
			*j = y - 1;
			break;
		case E:
			*i = x + 2;
			*j = y;
			break;
		case SE:
			*i = x + 1;
			*j = y + 1;
			break;
		case SW:
			*i = x - 1;
			*j = y + 1;
			break;
	}
}

/*void depositCrystal(Arena *A, Maquina *m, Directions d){
	if(m->crystals != 0){
		switch(d) {
			case W:
				grid[x+2][y]++;
				break;
			case NW:
				grid[x-1][y-1]++;
				break;
			case NE:
				grid[x+1][y-1]++;
				break;
			case E:
				grid[x+2][y]++;
				break;
			case SE:
				grid[x+1][y+1]++;
				break;
			case SW:
				grid[x-1][y+1]++;
				break;
		}
	}
}*/