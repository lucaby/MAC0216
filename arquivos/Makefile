# Variáveis #################################################
CC = gcc
CFLAGS = -std=c99 -w
EXECS = testAttackMachine testAtualiza testDepositCrystal testGetPosition testGrabCrystal testHasCrystal testInicializaGrid testInsereExercito testRemoveExercito testRemoveMortos testSysCall testTapaBuraco testMove
OBJ = testAttackMachine.o testAtualiza.o testDepositCrystal.o testGetPosition.o testGrabCrystal.o testHasCrystal.o testInicializaGrid.o testInsereExercito.o testRemoveExercito.o testRemoveMortos.o testSysCall.o testTapaBuraco.o testMove.o
HEADERS = maq.h arena.h structures.h instr.h pilha.h
DEPENDS = maq.c arena.c pilha.c



# Cria os arquivos-objeto de todos os testes ################
%.o: %.c $(CFLAGS) $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<



# Compila todos os arquivos-objetos #########################
all: $(OBJ)
	gcc $(CFLAGS) -o testAttackMachine testAttackMachine.o $(DEPENDS)
	gcc $(CFLAGS) -o testAtualiza testAtualiza.o $(DEPENDS)
	gcc $(CFLAGS) -o testDepositCrystal testDepositCrystal.o $(DEPENDS)
	gcc $(CFLAGS) -o testGetPosition testGetPosition.o $(DEPENDS)
	gcc $(CFLAGS) -o testGrabCrystal testGrabCrystal.o $(DEPENDS)
	gcc $(CFLAGS) -o testHasCrystal testHasCrystal.o $(DEPENDS)
	gcc $(CFLAGS) -o testInicializaGrid testInicializaGrid.o $(DEPENDS)
	gcc $(CFLAGS) -o testInsereExercito testInsereExercito.o $(DEPENDS)
	gcc $(CFLAGS) -o testMove testMove.o $(DEPENDS)
	gcc $(CFLAGS) -o testRemoveExercito testRemoveExercito.o $(DEPENDS)
	gcc $(CFLAGS) -o testRemoveMortos testRemoveMortos.o $(DEPENDS)
	gcc $(CFLAGS) -o testSysCall testSysCall.o $(DEPENDS)
	gcc $(CFLAGS) -o testTapaBuraco testTapaBuraco.o $(DEPENDS)



# CLEAN #####################################################
clean:
	rm -f $(EXECS) *.o