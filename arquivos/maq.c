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

	D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg));
	
			switch (opc) {
			  OPERANDO tmp;
			case PUSH:
			  empilha(pil, arg);
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
			  ip = arg;
			  continue;
			case JIT:
			  if (desempilha(pil) != 0) {
				ip = arg;
				continue;
			  }
			  break;
			case JIF:
			  if (desempilha(pil) == 0) {
				ip = arg;
				continue;
			  }
			  break;
			// Insiro o rbp na pilha de execução logo antes do ip
			case CALL:
			  empilha(exec, ip);
			  empilha(exec, rbp);
			  rbp = exec->topo;
			  ip = arg;
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
			  m->Mem[arg] = desempilha(pil);
			  break;
			case RCL:
			  empilha(pil,m->Mem[arg]);
			  break;
			case END:
			  return;
			case PRN:
			  printf("%d\n", desempilha(pil));
			  break;
			// Casos adicionados 
			case STL:
			  tmp = desempilha(pil);
			  exec->val[rbp + arg] = tmp;
			  break;
			case RCE:
			  tmp = exec->val[rbp + arg];
			  empilha(pil, tmp);
			  break;
			case ALC:
			// This might change
			// Salvar o valor da memória que foi armazenada para que ela seja liberada depois
		      exec->topo += arg;
		      empilha(exec, arg);
			  break;
			case FRE:
			// Test implementation
			  exec->topo -= desempilha(exec);
			  break;	
			}

			
	}
	

	D(imprime(pil,5));
	D(puts("\n"));

	ip++;
  }

void sysCall(Maquina *m, Tipo t, OPERANDO op){
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

void grabCrystal(Maquina *m, Directions d){
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
}

void depositCrystal(Arena *A, Maquina *m, Directions d){
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
}

void attackMachine(Maquina *m, Directions d){
	switch(d) {
		case W:
			m->x -= 2;
			break;
		case NW:
			m->x -= 1;
			m->y -= 1;
			break;
		case NE:
			m->x += 1;
			m->y -= 1;
			break;
		case E:
			m->x += 2;
			break;
		case SE:
			m->x += 1;
			m->y += 1;
			break;
		case SW:
			m->x -= 1;
			m->y += 1;
			break;
	}
}