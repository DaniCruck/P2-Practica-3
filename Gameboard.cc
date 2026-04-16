#include "Gameboard.h"
#include <stdexcept>

Gameboard::Gameboard(unsigned int height, unsigned int width){
    if((height < 10 || width < 10) && (height > 20 || width > 20)){
        throw std::invalid_argument("wrong board size");
    }
    else{
        this -> height = height;
        this -> width = width;
    }
}

Gameboard::~Gameboard(){
}

Piece Gameboard::*getContent(unsigned int row, unsigned int column){

}