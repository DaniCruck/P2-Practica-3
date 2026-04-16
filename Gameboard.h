#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Piece.h"
#include "Coordinate.h"
#include <vector>
#include <iostream>

class Gameboard{
    friend ostream& operator<<(ostream &os, Gameboard &g);
    private:
        unsigned int height;
        unsigned int width;
        vector<Piece> ***board;
    public:
        Gameboard(unsigned int height = 10, unsigned int width = 10);
        ~Gameboard();
        unsigned int getHeight() const {return height;}
        unsigned int getWidth() const {return width;}
        Piece *getContent();
        void setConten(int row, int column, Piece *p);
        void putPiece(const Coordinate &c, Piece *p);
        void removePiece(Piece *p);
        bool isLocationFree(const Coordinate &c, Piece *p) const;
};

#endif GAMEBOARD_H