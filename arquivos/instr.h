/* Códigos das instruções */
#ifndef INSTR_H
#define INSTR_H
//#include "structures.h"
//#include "maq.h"
#define MAXMEM 100

typedef enum {
  PUSH = 0,
  POP,
  DUP,
  ADD,
  SUB,
  MUL,
  DIV,
  JMP,
  JIT,
  JIF,
  CALL,
  RET,
  STS,
  RCS,
  EQ,
  GT,
  GE,
  LT,
  LE,
  NE,
  STO,
  RCL,
  END,
  PRN,
  STL,
  RCE,
  ALC,
  FRE,
  SYS,
  ATR,
  MOVE,
  GRAB,
  DEPO,
  ATTK
} OpCode;

typedef enum {
  NUM = 0,
  ACAO,
  VAR
} Tipo;

// Tipos de direções permitidas num grid hexagonal da maneira que implementamos
// Dada uma posição i,j o robô apenas tem como vizinhos as posições laterais e
// duas posições ao norte e ao sul

typedef enum {
  WEST = 0, // WEST
  NWEST, //NORTH WEST
  NEAST, //NORTH EAST
  EAST, // EAST
  SEAST, //SOUTH EAST
  SWEST //SOUTH WEST
} Direction;


// Até o momento, toda instrução que o usuário faz se resume a dois tipos:
// um inteiro ou uma direção onde a ação será realizada.
// Nesse sentido, optamos por declarar o OPERANDO dessa maneira:
typedef union {
  int n;
  Direction d;
}OPERANDO;


/* Instrução */

// Para que o usuário pudesse explicitar o tipo quando quiser realizar a operação, i.e.
// código da forma NUM PUSH 10 ou ACAO MOVE WEST optamos pode definir uma instrução assim:
typedef struct {
  Tipo t;
  OpCode instr;
  OPERANDO op;
} INSTR;

#endif
