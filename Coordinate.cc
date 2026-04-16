#include "Coordinate.h"

Coordinate::Coordinate(){
    row = 0;
    column = 0;
}

Coordinate::Coordinate(int row, int col){
    this -> row = row;
    column = col;
}

Coordinate::~Coordinate(){
}

Coordinate Coordinate::add(const Coordinate &other) const{
    return Coordinate(row + other.getRow(), column + other.getColumn());
}
 
ostream& operator<<(ostream &os, const Coordinate &c){
    os << '[' << c.row << ',' << c.column << ']';
    return os;
}