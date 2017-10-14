#ifndef STRUCTURES_H
#define STRUCTURES_H


typedef enum {
  ESTRADA = 0,
  RIO,
  MONTANHA,
  LAMA,
  CAMPO
} Terreno;

typedef enum {
  False = 0,
  True
}Bool;

typedef enum {
  BLUE = 0,
  RED
} Time;

typedef Bool Cristais;


typedef struct  {
  Bool isBase;
  Time team;
} Base; 

typedef struct {
  Bool ocupado;
  Time team;
} Ocupacao;



typedef struct {
  Terreno t;
  Base b;
  Cristais c;
  Ocupacao o;
} Celula;

typedef Celula** Grid;









#endif


/* Tipos dos operandos */
/* no momento, são todos inteiros */
