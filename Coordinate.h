#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
using namespace std;

class Coordinate{
    friend ostream& operator<<(ostream &os, const Coordinate &c);

    private:
        int row;
        int column;
    public:
        Coordinate(int row = 0, int col = 0);
        ~Coordinate();
        int getRow() const {return row;}
        int getColumn() const {return column;}
        Coordinate add(const Coordinate &other) {return row + other.getRow(), column + other.getColumn();}
        
};

#endif