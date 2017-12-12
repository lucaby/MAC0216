#include <stdio.h>
#include "maq.h"
//DONE
INSTR progB[] = {
  {ACAO, MOVE,  {0,NEAST}},
  {ACAO, MOVE,  {0,NEAST}},
  {ACAO, MOVE,  {0,NWEST}},
  {ACAO, MOVE,  {0,NWEST}},
  {ACAO, MOVE,  {0,NEAST}},
  {ACAO, MOVE,  {0,NEAST}},
  {ACAO, MOVE,  {0,NEAST}},
  {ACAO, MOVE,  {0,NEAST}},
  {ACAO, MOVE,  {0,WEST}},
  {ACAO, MOVE,  {0,WEST}}
};
INSTR progA[] = {

  {ACAO, MOVE,  {0,SEAST}},
  {ACAO, MOVE,  {0,SEAST}},
  {ACAO, MOVE,  {0,SEAST}},
  {ACAO, MOVE,  {0,SWEST}},
  {ACAO, MOVE,  {0,SEAST}},
  {ACAO, MOVE,  {0,SWEST}},
  {ACAO, MOVE,  {0,SWEST}},
  {NUM, END, {0, NEAST}},

};

int main() {
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 7, 14); 
  printf("Grid Inicializado.\n");

  InsereExercito(battlefield, 5, progA, BLUE);
  printf("Blue team off to work.\n");

  InsereExercito(battlefield, 5, progB, RED);
  printf("Red team off to work.\n");
  for(int i = 0; i < 11; i++) 
    Atualiza(battlefield, 1);
}