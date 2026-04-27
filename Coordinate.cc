// DNI 55392060X ILIEV ARKHIPOV , DANIEL VALERIEV
#include "Coordinate.h"
Coordinate::Coordinate(){
    row = 0;
    column = 0;
}

Coordinate::Coordinate(int row, int col){
    this -> row = row;
    this -> column = col;
}

Coordinate::~Coordinate(){
    
}

Coordinate Coordinate::add(const Coordinate &other) const{
    int newRow = this->row + other.getRow();
    int newCol = this->column + other.getColumn();
    Coordinate coord(newRow, newCol);
    return coord; 
}

ostream &operator<<(ostream &os, const Coordinate &c){
    os << '[' << c.getRow() << ',' << c.getColumn() << ']';
    return os;
}