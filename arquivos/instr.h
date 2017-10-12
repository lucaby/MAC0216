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
  SYS,
  ATR
} OpCode;

typedef enum {
  NUM,
  MOVE,
  GRAB,
  DEPO,
  ATTK
} Tipo;

/*typedef enum {
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
*/

/* } OPERANDO;
typedef int OPERANDO;*/

typdef struct {
    typedef enum {
    W, // WEST
    NW, //NORTH WEST
    NE, //NORTH EAST
    E, // EAST
    SE, //SOUTH EAST
    SW //SOUTH WEST

  } direction;
  /*union {
    int number;
    int action;
    int variable;
  };*/
} OPERANDO;


/* Instrução */
typedef struct {
  OpCode instr;
  Tipo t;
  OPERANDO op;
} INSTR;
