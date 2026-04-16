#ifndef PIECE_H
#define PIECE_H

#include "Shape.h"
#include "Coordinate.h"
#include <vector>
#include <iostream>

class Piece{
    friend ostream& operator<<(ostream &os, Piece &p);
    private:
        bool fixed;
        Orientation orientation;
        PieceType type;
    public:
        Piece();
        Piece(const Piece &other);
        ~Piece();
        bool isFixed() const {return fixed;}
        PieceType getType() const {return type;}
        Orientation getOrientation() const {return orientation;}
        void setFixed(bool fixed);
        void setOrientation(Orientation orientation);
        void rotateClockwise();
        void rotateCounterClockwise();
        vector<Coordinate> getFinalPositions(const Coordinate &c) const;
};

#endif PIECE_H