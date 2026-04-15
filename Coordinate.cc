#include "Coordinate.h"

Coordinate::~Coordinate(){
}
 
ostream& operator<<(ostream &os, const Coordinate &c){
    os << '[' << c.row << ',' << c.column << ']';
    return os;
}