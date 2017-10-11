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

/* } OPERANDO; */
typedef int OPERANDO;

typdef struct {
  Tipo t;
  Maquina **chamador;
  union {
    int n;
    int ac;
    int v;
  }
}
/* Instrução */
typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;
