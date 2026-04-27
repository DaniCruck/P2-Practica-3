// DNI 55392060X ILIEV ARKHIPOV , DANIEL VALERIEV
#ifndef _COORDINATE_H_
#define _COORDINATE_H_
#include <iostream>
using namespace std;
class Coordinate{
    friend ostream& operator<<(std::ostream &os,const Coordinate &c);
    private:
        int row;
        int column;
    public:
        Coordinate();
        Coordinate(int r, int c);
        ~Coordinate();
        int getRow() const {return row;}
        int getColumn() const {return column;}
        Coordinate add(const Coordinate &other) const;
};

#endif