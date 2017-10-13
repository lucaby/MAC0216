#include <stdio.h>
#include "maq.h"

INSTR prog[] = {


  {NUM, PUSH, 9},
  {NUM, CALL, 4},
  {NUM, PRN, 0},
  {NUM, END, 0},
  {NUM, ALC, 1},
  {NUM, DUP, 0},
  {NUM, STL, 0},
  {NUM, PUSH, 1},
  {NUM, EQ, 0},
  {NUM, JIF, 13},
  {NUM, PUSH, 1},
  {NUM, FRE, 1},
  {NUM, RET, 0},
  {NUM, RCE, 0},
  {NUM, PUSH, 1},
  {NUM, SUB, 0},
  {NUM, CALL, 4},
  {NUM, RCE, 0},
  {NUM, MUL, 0},
  {NUM, FRE, 1},
  {NUM, RET, 0},
};

int main(int ac, char **av) {
  Arena *a;
  Maquina *maq = cria_maquina(prog);
  exec_maquina(a, maq, 10000);
  destroi_maquina(maq, a);
  return 0;
}
