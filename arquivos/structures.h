typedef enum {
  false,
  true
}bool;

typedef enum {
  BLUE,
  RED
} Team;


/*typedef struct {
  Team time;
  Maquina[] *exercito;
}Time;*/

typedef Celula** Grid;


typedef struct {
  int n;
} Cristais;



typedef struct  {
  int isBase;
  Time team;
} Base; 

typedef struct {
  Terreno t;
  Base b;
  Cristais c;
  Ocupacao o;
} Celula;

typedef enum {
  ESTRADA,
  RIO,
  MONTANHA,
  LAMA,
  CAMPO
} Terreno;

typedef struct {
  bool ocupado;
  Team time;
} Ocupacao;

/* Tipos dos operandos */
/* no momento, são todos inteiros */
