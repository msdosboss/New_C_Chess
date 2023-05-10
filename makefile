all: main.o chess_func.o
	gcc main.o chess_func.o -o main

chess.o: main.c
	gcc -c main.c -o main.o

chess_func.o: chess_func.c
	gcc -c chess_func.c -o chess_func.o

clean:
	rm chess