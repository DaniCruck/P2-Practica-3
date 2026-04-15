OPTS=-g -Wall -std=c++11
OBJS=Gameboard.o Game.o Piece.o Coordinate.o Shape.o
CC=g++

prac3: $(OBJS) prac3.o
	$(CC) $(OPTS) $(OBJS) prac3.o -o prac3

prac3.o: prac3.cc Gameboard.h Game.h Piece.h Coordinate.h
	$(CC) $(OPTS) -c prac3.cc

Gameboard.o: Gameboard.cc Gameboard.h Piece.h Coordinate.h
	$(CC) $(OPTS) -c Gameboard.cc

Game.o: Game.cc Gameboard.h Game.h Piece.h Coordinate.h
	$(CC) $(OPTS) -c Game.cc

Coordinate.o: Coordinate.cc Coordinate.h
	$(CC) $(OPTS) -c Coordinate.cc

Shape.o: Shape.cc Shape.h
	$(CC) $(OPTS) -c Shape.cc

Piece.o: Piece.cc Piece.h Coordinate.h Shape.h
	$(CC) $(OPTS) -c Piece.cc

clean:
	rm $(OBJS)
