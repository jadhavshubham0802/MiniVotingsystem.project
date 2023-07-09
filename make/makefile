CC=gcc
CFLAGS=-c -Wall
INC=inc/
OBJ=obj/
SRC=src/
BIN=bin/

voting.out: $(OBJ)votingmain.o $(OBJ)voting.o
	$(CC) $(OBJ)votingmain.o $(OBJ)voting.o -o voting.out
	mv voting.out $(BIN)
$(OBJ)votingmain.o: $(SRC)votingmain.c
	$(CC) $(CFLAGS) $(SRC)votingmain.c -I $(INC)
	mv votingmain.o $(OBJ)
$(OBJ)voting.o: $(SRC)voting.c
	$(CC) $(CFLAGS) $(SRC)voting.c -I $(INC)
	mv voting.o $(OBJ)
clean:
	rm -f $(OBJ)*.o
	rm -f $(BIN)*.out

