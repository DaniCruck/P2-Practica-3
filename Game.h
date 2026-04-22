#ifndef GAME_H
#define GAME_H

#include "Gameboard.h"
#include "Piece.h"
#include "Coordinate.h"

class Game{

    friend ostream& operator<<(ostream &os, const Game &g);

    private:
        bool gameOver;
        Gameboard gameBoard;
        Piece *currentPiece;
        Coordinate currentPosition;
    public:
        Game(unsigned int height, unsigned int width);
        ~Game();
        bool nextPiece();
        void moveLeft();
        void moveRight();
        void moveDown();
        void rotateClockwise();
        void rotateCounterClockwise();
        bool isPieceFixed() const;
        bool isGameOver() const;
        Piece *getCurrentPiece() const {return currentPiece;}
        Coordinate getCurrentPosition() const {return currentPosition;}
        Gameboard &getGamebiard() {return gameBoard;}
        void setCurrentPiece(Piece *p);
        void setCurrentPosition(const Coordinate &c); 
};

#endif