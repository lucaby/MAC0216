/* Códigos das instruções */
#include "structures.h"

typedef enum {
  PUSH,
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
  ATR
} OpCode;

typedef enum {
  NUM,
  ACAO,
  VAR

} Tipo;

typedef enum {
  PUNCH,
  KICK,
  THROW,
  SLICE
} Attack;

typedef enum {
  MOVE,
  GRAB,
  CHCK
} Action;

typedef enum {
  W, // WEST
  NW, //NORTH WEST
  NE, //NORTH EAST
  E, // EAST
  SE, //SOUTH EAST
  SW //SOUTH WEST

} Directions;

/* } OPERANDO;
typedef int OPERANDO;*/

typdef struct {
  Tipo t;
  Maquina **chamador;
  union {
    int number;
    int action;
    int variable;
  };
} OPERANDO;

/* Instrução */
typedef struct {
  OpCode instr;
  Tipo t;
  OPERANDO op;
} INSTR;
