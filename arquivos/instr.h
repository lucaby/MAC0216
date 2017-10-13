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

typedef enum {
  WEST = 0, // WEST
  NWEST, //NORTH WEST
  NEAST, //NORTH EAST
  EAST, // EAST
  SEAST, //SOUTH EAST
  SWEST //SOUTH WEST
} Direction;

typedef union {
  int n;
  Direction d;
}OPERANDO;


/* Instrução */
typedef struct {
  Tipo t;
  OpCode instr;
  OPERANDO op;
} INSTR;

#endif
