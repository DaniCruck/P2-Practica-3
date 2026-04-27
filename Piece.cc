// DNI 55392060X ILIEV ARKHIPOV , DANIEL VALERIEV
#include "Piece.h"

Piece::Piece(){
    fixed = false;
    orientation = D0;
    type = Shape::getRandomPieceType();
}

Piece::Piece(const Piece &other){
    fixed = other.fixed;
    orientation = other.orientation;
    type = other.type;
}

Piece::~Piece(){

}

void Piece::rotateClockwise(){
    switch (this->getOrientation()){
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
    switch(this->getOrientation()){
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

vector<Coordinate> Piece::getFinalPositions(const Coordinate &coord) const{
    vector<Coordinate> shapeCoords;
    int **shape = Shape::getShape(orientation, type);
    for(unsigned int i = 0; i < kSHAPESIZE; i++){
        for(unsigned int j = 0; j < kSHAPESIZE; j++){
            if(shape[i][j] == 1){
                Coordinate tempCord(coord.getRow() + i, coord.getColumn() + j);
                shapeCoords.push_back(tempCord);
                tempCord.~Coordinate();
            }
        }
    }

    for(unsigned int i = 0; i < kSHAPESIZE; i++){
        delete[] shape[i];
    }
    delete[] shape;
    return shapeCoords;
}

ostream& operator<<(ostream &os, Piece &p){
    os << "[type=" << p.type << ", fixed=" << p.fixed << ", orientation=" << p.orientation << ']' << '\n';
    return os;
}