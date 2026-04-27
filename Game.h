// DNI 55392060X ILIEV ARKHIPOV , DANIEL VALERIEV
#ifndef _GAME_H_
#define _GAME_H_
#include "Coordinate.h"
#include "Gameboard.h"
#include "Piece.h"
class Game{
    friend ostream& operator<<(ostream& os, Game &g);
    private:
        bool gameOver;
        Coordinate currentPosition;
        Gameboard gameBoard;
        Piece *currentPiece;
    public:
        Game(unsigned int height, unsigned int width);
        ~Game();
        bool nextPiece();
        void moveLeft();
        void moveRight();
        void moveDown();
        void rotateClockwise();
        void rotateCounterClockwise();
        bool isGameOver() const {return gameOver;}
        bool isPieceFixed() const {return currentPiece->isFixed();}
        Piece *getCurrentPiece() const {return currentPiece;}
        Coordinate getCurrentPosition() const {return currentPosition;}
        Gameboard &getGameboard() {return gameBoard;}
        void setCurrentPiece(Piece *p) {currentPiece = p;}
        void setCurrentPosition(const Coordinate &c) {currentPosition = c;}
};

#endif