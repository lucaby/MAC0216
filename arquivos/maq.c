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
	/* (maquina, direção, i, j) -> null
	Dada uma Maquina m na posição (x,y), inserimos em i e j a 
	posição correspondente a direção que o usuário chamou o sistema
	para efetuar a ação. */
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

OPERANDO moveMachine(Arena *A, Maquina *m, Direction d){
	/*(arena, maquina, direção) -> operando (true or false)
	Quando o usuário chama o sistema para efetuar um movimento
	esta função verifica se a posição requerida está livre para a ação
	e muda a posição do robô em caso afirmativo. Devolve um operando 
	tal qual sua parte inteira indica se a ação conseguiu ser realizada ou não.*/
	int i, j;
	OPERANDO result;
	result.n = False;
	directionsSwitch(m, d, &i, &j);
	if(notOcupied(A->grid, i, j)){
		x += i;
		y += j;
		result.n = True;
	}
	return result;
}

OPERANDO grabCrystal(Arena *A, Maquina *m, Direction d){
	/*(arena, maquina, direção) -> operando (true or false)
	Quando o usuário chama o sistema para pegar um cristal que está na
	posição referente a direção d, esta função verifica se há cristais
	na posição e atualiza a quantidade de cristais do robô e do local caso
	afirmativo. Devolve um operando que tem a  parte inteira indicando
	se a ação conseguiu ser realizada ou não.*/
	int i, j;
	OPERANDO result;
	result.n = False;
	directionsSwitch(m, d, &i, &j);
	if(hasCrystal(A->grid, i, j)) {
		A->grid[i][j].c--;
		(m->crystals)++;
		result.n = True;
	}
	return result;
}

OPERANDO depositCrystal(Arena *A, Maquina *m, Direction d) {
	/*(arena, maquina, direção) -> operando (true or false)
	Neste caso, dada a chamada de sistema para depositar um cristal numa 
	direção d, é verificado se o robô possui algum cristal. Caso tenha, atualizamos
	a quantidade de cristais do robô e da posição do grid onde foi depositado.
	Devolvemos um OPERANDO indicando se a operação foi bem sucedida.*/
	int i, j;
	OPERANDO result;
	result.n = False;
	directionsSwitch(m, d, &i, &j);
	if(m->crystals > 0){
		A->grid[i][j].c++;
		m->crystals--;
		result.n = True;
	}
	return result;
}

OPERANDO attackMachine(Arena *A, Maquina *m, Direction d) {
	/*(arena, maquina, direção) -> operando (true or false)
	Por simplicidade quanto ao sistema de hit points dos robôs, seus respectivos
	pontos de ataque e defesa, apenas imprimimos uma mensagem na saída padrão
	indicando que o ataque foi realizado. Devolvemos também a indicação desse resultado.*/
	int i, j;
	OPERANDO result;
	result.n = False;
	directionsSwitch(m, d, &i, &j);
	if(hasEnemy(A->grid, i, j,m->t)){
		printf("EXTERMINATE!");
		result.n = True;
	}
	return result;

}


OPERANDO sysCall(Arena *A, Maquina *m, OpCode t, Direction op){
	/*(arena, maquina, ação, direção) -> operando (true or false)
	Apenas delega, dependendo da ação (OpCode t) qual das funções
	devem ser chamadas e retorna o resultado.*/
	OPERANDO result;
	switch(t) {
		case MOVE:
			result = moveMachine(A, m, op);
			break;
		case GRAB:
			result = grabCrystal(A, m, op);
			break;
		case DEPO:
			result = depositCrystal(A, m, op);
			break;
		case ATTK:
			result = attackMachine(A, m, op);
			break;
	}
	return result;
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
					  exec->topo -= desempilha(exec).n;
					  break;

					// A partir daqui implementamos as coisas para a Fase II
					case ATR:
					/*Pega o OPERANDO do topo da pilha e empilha um OPERANDO com
					o atributo de número arg desse OPERANDO.*/
						tmp = desempilha(pil);
					// Dependendo do argumento (0, 1, 2, 3) devemos empilhar operandos
					// de maneiras diferentes. Da mesma forma, o PRN deve mudar
					// para se adequar ao print de operandos.
						empilha(pil, tmp);
						break;
				}
				break;
			case ACAO:
				/*Chama a função sysCall, que delega uma determinada ação opc,
				e empilha o resultado desta ação (se foi realizada ou não).*/
				empilha(pil, sysCall(A, m, opc, arg.d));
				break;
			
			case VAR:

				break;
				
	}
	D(imprime(pil,5));
	D(puts("\n"));

	ip++;
  }
}

















