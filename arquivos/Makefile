# Variáveis #################################################
CC = gcc
EXECS = testAttackMachine testAtualiza testDepositCrystal testGetPosition testGrabCrystal testHasCrystal testInicializaGrid testInsereExercito testRemoveExercito testRemoveMortos testSysCall testTapaBuraco testMove
OBJ = testAttackMachine.o testAtualiza.o testDepositCrystal.o testGetPosition.o testGrabCrystal.o testHasCrystal.o testInicializaGrid.o testInsereExercito.o testRemoveExercito.o testRemoveMortos.o testSysCall.o testTapaBuraco.o testMove.o
HEADERS = maq.h arena.h structures.h instr.h pilha.h
DEPENDS = maq.o arena.o pilha.o



# Cria os arquivos-objeto de todos os testes ################
%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $<



# Compila todos os arquivos-objetos #########################
all: $(OBJ)
	gcc -o testAttackMachine testAttackMachine.o $(DEPENDS)
	gcc -o testAtualiza testAtualiza.o $(DEPENDS)
	gcc -o testDepositCrystal testDepositCrystal.o $(DEPENDS)
	gcc -o testGetPosition testGetPosition.o $(DEPENDS)
	gcc -o testGrabCrystal testGrabCrystal.o $(DEPENDS)
	gcc -o testHasCrystal testHasCrystal.o $(DEPENDS)
	gcc -o testInicializaGrid testInicializaGrid.o $(DEPENDS)
	gcc -o testInsereExercito testInsereExercito.o $(DEPENDS)
	gcc -o testMove testMove.o $(DEPENDS)
	gcc -o testRemoveExercito testRemoveExercito.o $(DEPENDS)
	gcc -o testRemoveMortos testRemoveMortos.o $(DEPENDS)
	gcc -o testSysCall testSysCall.o $(DEPENDS)
	gcc -o testTapaBuraco testTapaBuraco.o $(DEPENDS)



# CLEAN #####################################################
clean:
	rm -f $(EXECS) *.o