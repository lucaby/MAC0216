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

// Os tipos a seguir são referentes aos componentes de uma célula do Grid hexagonal
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


// Uma célula, ou um hexagono do nosso grid, possui os seguintes componentes:
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
