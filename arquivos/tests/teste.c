#include <stdio.h>
#include "maq.h"

INSTR prog[] = {
  {PUSH, NUM, 55},
  {PUSH, NUM, 7},
  {PUSH, NUM, 5},
  {CALL, NUM, 5},
  {END, NUM, 0},
  {ALC, NUM, 3},
  {STL, NUM, 0},
  {STL, NUM, 1},
  {STL, NUM, 2},
  {PRN, NUM, 0},
  {RCE, NUM, 2},
  {RCE, NUM, 1},
  {RCE, NUM, 0},
  {FRE, NUM, 0},


};

int main(int ac, char **av) {
  Maquina *maq = cria_maquina(prog);
  exec_maquina(maq, 1000);
  destroi_maquina(maq);
  return 0;
}
