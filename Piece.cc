#include "Piece.h"

Piece::Piece(){
    fixed = false;
    orientation = D0;
    type = Shape::getRandomPieceType();
}

Piece::Piece(const Piece &other){
    fixed = other.isFixed();
    orientation = other.getOrientation();
    type = other.getType();
}

Piece::~Piece(){
}

void Piece::setFixed(bool fixed){
    this -> fixed = fixed;
}

void Piece::setOrientation(Orientation orientation){
    this -> orientation = orientation;
}

void Piece::rotateClockwise(){
    switch(orientation){
        case D0:
            orientation = D270;
            break;
        case D90:
            orientation = D0;
            break;
        case D180:
            orientation = D90;
            break;
        case D270:
            orientation = D180;
            break;
    }
}

void Piece::rotateCounterClockwise(){
    switch(orientation){
        case D0:
            orientation = D90;
            break;
        case D90:
            orientation = D180;
            break;
        case D180:
            orientation = D270;
            break;
        case D270:
            orientation = D0;
            break;
    }
}

vector<Coordinate> Piece::getFinalPositions(const Coordinate &c) const{
    vector<Coordinate> shapeCoord;
    int **shape = Shape::getShape(orientation,type);
    for(int i = c.getRow(); i <c.getRow() + 4; i++){
        for(int j = c.getColumn(); j <c.getColumn() + 4; j++){
            if(shape[i][j] == 1){
                Coordinate tempCord(i, j);
                shapeCoord.push_back(tempCord);
                tempCord.~Coordinate();
            }
        }
    }
    delete shape;
    return shapeCoord;
}

ostream &operator<<(ostream &os, const Piece &p){
    os << '[' << "type=";
    switch (p.getType()){
        case PT_I:
            os << "I, ";
            break;
        case PT_J:
            os << "J, ";
            break;
        case PT_L:
            os << "L, ";
            break;
        case PT_O:
            os << "O, ";
            break;
        case PT_S:
            os << "S, ";
            break;
        case PT_Z:
            os << "Z, ";
            break;
        case PT_T:
            os << "T, ";
            break;
    }
    os << "fixed=" << p.isFixed() << ", " << "orientation=";
    switch(p.getOrientation()){
        case D0:
            os << "0]" << '\n';
            break;
        case D90:
            os << "90]" << '\n';
            break;
        case D180:
            os << "180]" << '\n';
            break;
        case D270:
            os << "270]" << '\n';
            break;
    }
}