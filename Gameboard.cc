// DNI 55392060X ILIEV ARKHIPOV , DANIEL VALERIEV
#include "Gameboard.h"

Gameboard::Gameboard(unsigned int height, unsigned int width){
    if((height < 10 || width < 10) || (height > 20 || width > 20)){
        throw invalid_argument("wrong board size");
    }
    else{
        this->height = height;
        this->width = width;

        board = new Piece **[this->height];
        for(unsigned int i = 0; i < this->height; i++){
            board[i] = new Piece *[this->width];
            for(unsigned int j = 0; j < this->width; j++){
                board[i][j] = nullptr;
            }
        }
    }
}

Gameboard:: ~Gameboard(){

}

Piece* Gameboard::getContent(int row, int column) const{
    Piece *content = nullptr;
    if (row >= 0 && (unsigned int)row < height && column >= 0 && (unsigned int)column < width){
        content = board[row][column];
    }
    return content;
}

void Gameboard::setContent(int row,int column,Piece *p){
    if (row >= 0 && (unsigned int)row < height && column >= 0 && (unsigned int)column < width){
        board[row][column] = p;
    }
}

void Gameboard::putPiece(const Coordinate &c, Piece *p){
    vector<Coordinate> pieceCords = p->getFinalPositions(c);
    for(unsigned int i = 0; i < pieceCords.size(); i++){
        setContent(pieceCords[i].getRow(), pieceCords[i].getColumn(), p);
    }
}

void Gameboard::removePiece(Piece *p){
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            if(board[i][j] == p){
                board[i][j] = nullptr;
            }
        }
    }
}

bool Gameboard::isLocationFree(const Coordinate &c, Piece *p) const{
    bool isFree = true;
    vector<Coordinate> pieceCords = p->getFinalPositions(c);
    for(unsigned int i = 0; i < pieceCords.size() && isFree; i++){
        int row = pieceCords[i].getRow();
        int col = pieceCords[i].getColumn();
        if(row < 0 || row >= (int)height || col < 0 || col >= (int)width){
            isFree = false;
        }
        else {
            Piece* tempPiece = getContent(row,col);
            if(tempPiece != nullptr && tempPiece->isFixed()){
                isFree = false; // Chocó con una pieza fijada
            }
        }
    }
    return isFree;
}

ostream& operator<<(ostream &os, const Gameboard &g){
    for(unsigned int i = 0; i < g.getHeight(); i++){
        os << '|';
        for(unsigned int j = 0; j < g.getWidth(); j++){
            Piece* actPiece = g.getContent(i,j);
            if(actPiece == nullptr){
                os << ' ';
            }else if(actPiece->isFixed()){
                os << '@';
            }else{
                os << '#';
            }
        }
        os << '|' << '\n';
    }
    for(unsigned int i = 0; i < g.getWidth() + 2; i++){
        os << '=';
    }
    os << '\n';
    return os;
}