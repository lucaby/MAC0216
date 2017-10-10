/* Códigos das instruções */
typedef enum {
  BLUE
  RED
} Time;

typedef enum {
  FALSE,
  TRUE;
}
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
  FRE
} OpCode;

typedef struct {
  int n;
} Cristais;

typedef struct {
  int busy;
} Ocupacao;

typedef struct 
{
  int isBase;
  Time team;
} Base; 

typedef struct {
  Terreno t;
  Base b;
  Cristais c;
  Ocupacao o;
}

typedef enum {
  ESTRADA,
  RIO,
  MONTANHA,
  LAMA,
  CAMPO
} Terreno;
/* Tipos dos operandos */
/* no momento, são todos inteiros */
typedef enum {
  NUM,
  ACAO,
  VAR
} Tipo;

/* Operando */
/* typedef struct { */
/*   Tipo t; */
/*   union { */
/* 	int n; */
/* 	int ac; */
/* 	int v; */
/*   }; */
/* } OPERANDO; */
typedef int OPERANDO;

/* Instrução */
typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;
