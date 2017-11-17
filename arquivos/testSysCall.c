#include <stdio.h>
#include "maq.h"

INSTR prog[] = {
  /* It should be able, if in [0,1] to move EAST, then NEAST.
  Will place crystals in WEST so it should be able to grab then
  Then, again, place them at EAST and check its value. Will put 
  enemy in EAST and a non enemy in WEST to test ATTK values.
  Then, will make a specific type of Cell to test ATR calls. 
  That way testing all sysCalls functions at once and getting their
  results.*/
  //Initial values of col and lin x = 1, y = 0

  //{ACAO, MOVE,  {0, EAST}},
  //Moved to y = 0, x = 3. Should print 1
  {ACAO, GRAB, {0, EAST}},
  {ACAO, MOVE,  {0, EAST}},
  //Moved to y = 0, x = 5. Should print 1
  //{NUM, PRN, {0, WEST}},
  {ACAO, MOVE,  {0, NEAST}},
  //Tried to move to y = -1, x = 4. Should print 0
  //{NUM, PRN, {0, WEST}},
  //{ACAO, MOVE,  {0, SWEST}},
  //{ACAO, MOVE,  {0, SEAST}},
  //{ACAO, MOVE,  {0, SWEST}},
  //{ACAO, MOVE,  {0, EAST}},
  //Grabbed in y = 0, x = 3 . SHould print 1
  //{NUM, PRN, {0, WEST}},
  //{ACAO, DEPO,  {0, EAST}},
  //Deposited in y = 0, x = 7. Should print 1
  //{NUM, PRN, {0, WEST}},
  /*{ACAO, ATTK,  {0, EAST}},
  //Attacked on y = 0, x = 7. Sould print EXTERMINATE and 1
  {NUM, PRN, {0, WEST}},
  {ACAO, ATTK,  {0, SEAST}},
  //Attacked on y = 1, x = 6. Should print 0
  {NUM, PRN, {0, WEST}},
  {ACAO, DEPO,  {0, SWEST}},
  //Deposited in y = 1, x = 4. Should print 0
  {NUM, PRN, {0, WEST}},
  {ACAO, GRAB,  {0, WEST}},
  //Tried to grab crystal in y = 0, x = 3. Should print 0
  {NUM, PRN, {0, WEST}},
  {ACAO, DEPO,  {0, SWEST}},
  //Deposits crystal in y = 1, x = 4. Should print 0
  {NUM, PRN, {0, WEST}},
  {INTER, PUSH, {0, NEAST}},
  //Tried to push NEAST CELL y = -1, x = 6
  {NUM, ATR,  {3, WEST}},
  //Gives INvalid Cell
  {NUM, PRN, {0, WEST}},
  //Will cause error if empty cell
  {INTER, PUSH,  {0, WEST}},
  //PUSH in stack WEST CELL y = 0, x = 3
  {NUM, ATR,  {3, WEST}},
  {NUM, PRN, {0, WEST}},
  //Prints if ocupied
  {INTER, PUSH,  {0, WEST}},
  {NUM, ATR,  {2, WEST}},
  {NUM, PRN, {0, WEST}},
  //Prints number of crystals. Sould display 0
  {INTER, PUSH,  {0, WEST}},
  {NUM, ATR,  {1, WEST}},
  {NUM, PRN, {0, WEST}},
  //Prints if it is Base, should display 0
  {INTER, PUSH,  {0, WEST}},
  {NUM, ATR, {0, WEST}},
  {NUM, PRN, {0, WEST}},
  */
  //Prints out corresponding terrain number
  {NUM, END, {0, WEST}},
  

};

int main() {
  Arena* battlefield = malloc(sizeof(Arena));
  printf("Arena feita.\n");

  inicializaArena(battlefield, 7, 14); 

  printf("Grid Inicializado.\n");
InsereExercito(battlefield, 1, prog, BLUE);
  InsereExercito(battlefield, 1, prog, RED);
  printf("Blue team off to work.\n");


  //Attacking
 /* battlefield->exercitos[1]->x = 7;
  battlefield->exercitos[1]->y = 0;
  battlefield->grid[0][7].o.ocupado = True;
  battlefield->grid[0][7].o.team = RED;

  //Grabing Crystals
  if(battlefield->grid[0][3].c == 0)
    battlefield->grid[0][3].c++;
  else if(battlefield->grid[0][3].c > 1)
    battlefield->grid[0][3].c = 1;*/


  //Moving
  //printf("%d %d \n", battlefield->exercitos[0]->x, battlefield->exercitos[0]->y);

  for(int i = 0; i < 50; i++)
    Atualiza(battlefield, 1);
  closeArena(battlefield);
  /*After executing, the output by the prints should be:
  1, 1, 0, 1, 1, EXTERMINATE!, 1, 0, 0, 0, 0, Celula Invalida, Pilha Vazia, 12, 1, 0, 0, random int */
}