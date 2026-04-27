// DNI 55392060X ILIEV ARKHIPOV , DANIEL VALERIEV
#ifndef _PIECE_H_
#define _PIECE_H_
#include <vector>
#include "Shape.h"
#include "Coordinate.h"

class Piece{
    friend std::ostream& operator<<(ostream &os, Piece &p);
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
        void setFixed(bool fixed) {this->fixed = fixed;}
        void setOrientation(Orientation orientation) {this->orientation = orientation;}
        void rotateClockwise();
        void rotateCounterClockwise();
        vector<Coordinate> getFinalPositions(const Coordinate &c) const;
};

#endif