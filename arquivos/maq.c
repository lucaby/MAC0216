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
#define exec (&m->exec)
#define prg (m->prog)
#define rbp (m->rbp)


static void Erro(char *msg) {
  fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Maquina *cria_maquina(INSTR *p, int x, int y) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));

  if (!m) Fatal("Memória insuficiente",4);
  m->pil = *cria_pilha();
  ip = 0;
  prg = p;
  rbp = 0;
  // Detalhe importante: x é coluna e y é linha
  m->x = x;
  m->y = y;
  m->crystals = 0;
  m->alive = True;
  m->time = 0;
  m->hp = 100;
  return m;
}
#define pil (&m->pil)
void destroi_maquina(Maquina *m, Arena *arena) {
  free(m);
  free(arena);
}

/* Novas funções para as chamadas de sistema */


void exec_maquina(Arena *arena, Maquina *m, int n) {
  int i;
  exec->topo = 0;
  pil->topo = 0;
  for (i = 0; i < n; i++) {
	Tipo    tipo = prg[ip].t;
	OpCode   opc = prg[ip].instr;
	OPERANDO arg = prg[ip].op;
  	/* printf("i: %d\n opc: %d\n arg: %u\n", i, opc, arg); */
	//printf("topo %d\n", pil->topo);
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
					  exec->topo -= desempilha(exec).n;
					  break;

					// arena partir daqui implementamos as coisas para a Fase II
					case ATR:
						/*Pega o OPERANDO do topo da pilha e empilha um OPERANDO com
						o atributo de número arg desse OPERANDO.*/
						tmp = desempilha(pil);
						int i = -1, j = -1;
						getPosition(m, tmp.d, &i, &j, arena->rows, arena->cols);
						if(i != -1){
							switch(arg.n){
								case 0:
									tmp.n = (int)(arena->grid[i][j].t);
									empilha(pil, tmp);
									break;
								case 1:
									tmp.n = (int)(arena->grid[i][j].b.isBase);
									empilha(pil, tmp);
									break;
								case 2:
									tmp.n = (int)(arena->grid[i][j].c);
									empilha(pil, tmp);

									break;
								case 3:
									tmp.n = (int)(arena->grid[i][j].o.ocupado);
									empilha(pil, tmp);
									break;
							}
						}
						else
							printf("Celula invalida.\n");

						// Dependendo do argumento (0, 1, 2, 3) devemos empilhar operandos
						// de maneiras diferentes. Da mesma forma, o PRN deve mudar
						// para se adequar ao print de operandos.
							
						break;
				}
				break;
			case ACAO:
				/*Chama a função sysCall, que delega uma determinada ação opc,
				e empilha o resultado desta ação (se foi realizada ou não).*/
				empilha(pil,sysCall(arena, m, opc, arg.d));
				break;

			
			case INTER:
				switch(opc) {
					case PUSH:
						empilha(pil, arg);
				}

				break;
				
	}
	D(imprime(pil,5));
	D(puts("\n"));

	ip++;
  }
}

















