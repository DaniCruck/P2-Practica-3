// DNI 55392060X ILIEV ARKHIPOV , DANIEL VALERIEV
#include "Game.h"

Game::Game(unsigned int height, unsigned int width){
    gameBoard = Gameboard(height, width);
    currentPiece = nullptr;
    gameOver = false;
    currentPosition = Coordinate();
}

Game::~Game(){

}

bool Game::nextPiece(){
    bool canPlace;
    unsigned int initialCol = (gameBoard.getWidth() - kSHAPESIZE) / 2;
    Coordinate initialPos(0, initialCol);
    Piece *newPiece = new Piece();

    if(gameBoard.isLocationFree(initialPos, newPiece)){
        currentPosition = initialPos;
        currentPiece = newPiece;
        canPlace = true;
        gameBoard.putPiece(currentPosition, currentPiece);
    }
    else{
        canPlace = false;
        gameOver = true;
    }

    return canPlace;
}

void Game::moveLeft(){
    Coordinate left(0,-1);
    if(!currentPiece->isFixed()){
        Coordinate newPos = currentPosition.add(left);
        if(gameBoard.isLocationFree(newPos, currentPiece)){
            gameBoard.removePiece(currentPiece);
            currentPosition = newPos;
            gameBoard.putPiece(currentPosition, currentPiece);
        }
    }
}

void Game::moveRight(){
    Coordinate right(0,1);
    if(!currentPiece->isFixed()){
        Coordinate newPos = currentPosition.add(right);
        if(gameBoard.isLocationFree(newPos, currentPiece)){
            gameBoard.removePiece(currentPiece);
            currentPosition = newPos;
            gameBoard.putPiece(currentPosition, currentPiece);
        }
    }
}

void Game::moveDown(){
    Coordinate down(1,0);
    if(!currentPiece->isFixed()){
        Coordinate newPos = currentPosition.add(down);
        if(gameBoard.isLocationFree(newPos, currentPiece)){
            gameBoard.removePiece(currentPiece);
            currentPosition = newPos;
            gameBoard.putPiece(currentPosition, currentPiece);
        }
        else{
            currentPiece->setFixed(true);
        }
    }
}

void Game::rotateClockwise(){
    if(!gameOver && !currentPiece->isFixed()){
        currentPiece->rotateClockwise();
        gameBoard.removePiece(currentPiece);
        gameBoard.putPiece(currentPosition, currentPiece);
    }
}

void Game::rotateCounterClockwise(){
    if(!gameOver && !currentPiece->isFixed()){
        currentPiece->rotateCounterClockwise();
        gameBoard.removePiece(currentPiece);
        gameBoard.putPiece(currentPosition, currentPiece);
    }
}

ostream& operator<<(ostream& os, Game &g){
    os << g.getGameboard();
    return os;
}