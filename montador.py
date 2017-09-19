#!/usr/bin/python3

"""
Lê, na entrada padrão, um programa na linguagem de montagem da máquina
virtual e retorna um programa em C que executa este programa.

Uso:
    montador < entrada > saida
"""
from sys import stdin

l = stdin.readline()
ip = 0

tabsim = {}

#Adiciona os includes necessarios
print("#include <stdio.h>")
print("#include \"maq.h\"")
print()


print("INSTR prog[] = {")
while l:
    label = op = ""
    arg   = 0
    try:
        l = l[:l.index('#')]
    except:
        pass
    keys = l.split()
    if len(keys) > 0 and keys[0].endswith(":"):
        label = keys[0][:-1]              #jogando fora o ':'
        tabsim[label]=ip
        keys.pop(0)
    if len(keys) > 0:
        op = keys.pop(0)
    if len(keys) > 0:
        arg = keys.pop(0)
        if arg in tabsim:
            arg = tabsim[arg]
    if op != "":
        print("  {%s, %s},"%(op,arg))
    else:
        print()
    l = stdin.readline()
    ip += 1
print("};\n")
    


# Numero de interacoes da maquina
n = 1000

#Criacao da main
print("int main(int ac, char **av) {")
print("  Maquina *maq = cria_maquina(prog);")
print("  exec_maquina(maq, {});".format(n))
print("  destroi_maquina(maq);")
print("  return 0;")
print("}")


# Local variables:
# mode: python
# End: