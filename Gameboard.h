// DNI 55392060X ILIEV ARKHIPOV , DANIEL VALERIEV
#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_
#include "Piece.h"
#include <stdexcept>

class Gameboard{
    friend ostream& operator<<(ostream &os, const Gameboard &g);
    private:
        unsigned int height;
        unsigned int width;
        Piece ***board;
    public:
        Gameboard(unsigned int height = 10, unsigned int width = 10);
        ~Gameboard();
        unsigned int getHeight() const {return height;}
        unsigned int getWidth() const {return width;}
        Piece *getContent(int row, int col) const;
        void setContent(int row,int column,Piece *p);
        void putPiece(const Coordinate &c, Piece *p);
        void removePiece(Piece *p);
        bool isLocationFree(const Coordinate &c, Piece *p) const;
};

#endif