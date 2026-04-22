#include "Gameboard.h"
#include <stdexcept>

Gameboard::Gameboard(unsigned int height, unsigned int width){
    if((height < 10 || width < 10) && (height > 20 || width > 20)){
        throw std::invalid_argument("wrong board size");
    }
    else{
        this -> height = height;
        this -> width = width;
        //Inicializamos el tablero
        board = new Piece **[height];
        for(unsigned int i = 0; i < height; i++){
            board[i] = new Piece *[width];
            for(unsigned int j = 0; j < width; j++){
                board[i][j] = NULL;
            }
        }
    }
}

Gameboard::~Gameboard(){
    for(unsigned int i = 0; i < height; i++){
        delete[] board[i];
    }
    delete[] board;
}

Piece* Gameboard::getContent(unsigned int row,unsigned int column) const{
    Piece* result = NULL;
    //Comprobamos que la fila y columna estén dentro del rango.
    if((row >= 0 && row < height) && (column >= 0 && column < width)){
        result = board[row][column];
    }
    return result;
}

void Gameboard::setContent(unsigned int row,unsigned int column, Piece* p){
    if((row >= 0 && row < height) && (column >= 0 && column < width)){
        board[row][column] = p;
    }
}

void Gameboard::putPiece(const Coordinate &c, Piece *p){
    vector<Coordinate> piecePosition = p->getFinalPositions(c);

    for(unsigned int i = 0; i < piecePosition.size(); i++){
        Coordinate pos = piecePosition[i];
        setContent(pos.getRow(), pos.getColumn(),p);
    }
}

void Gameboard::removePiece(Piece* p){
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            if(board[i][j] == p){
                board[i][j] = NULL;
            }
        }
    }
}

bool Gameboard::isLocationFree(const Coordinate &c, Piece *p) const{
    bool isFree = true;
    vector<Coordinate> positions = p->getFinalPositions(c);
    for(unsigned int i = 0; i < positions.size() && isFree; i++){
        unsigned int row = positions[i].getRow();
        unsigned int col = positions[i].getColumn();
        
        // 1. Si se sale del tablero, ya no está libre
        if(row < 0 || row >= height || col < 0 || col >= width){
            isFree = false;
        }
        else {
            // 2. Comprobamos si la casilla está ocupada
            Piece *content = getContent(row, col);
            if(content != nullptr){
                // Si hay una pieza, revisamos si está fijada
                if(content->isFixed() && content != p){
                    isFree = false;
                }
            }
        }
    }
    return isFree;
}

ostream& operator<<(ostream &os, Gameboard &g){
    for(unsigned int i = 0; i < g.getHeight(); i++){
        os << '|';
        for(unsigned int j = 0; j < g.getWidth(); j++){
            Piece *p = g.getContent(i, j);
            if(p == NULL){
                os << " ";
            }
            else if(p -> isFixed()){
                os << "@";
            }
            else{
                os << "#";
            }
        }
        os << "|\n";
    }
    for(unsigned int i = 0; i < g.getWidth(); i++){
        os << "=";
    }
    os << "\n";
    return os;
}