#include "Game.h"

Game::Game(unsigned int height, unsigned int width){
    gameBoard = Gameboard(height, width);
    currentPiece = NULL;
    gameOver = false;
    currentPosition = Coordinate();
}

bool Game::nextPiece(){
    bool canPlace;
    int spawnColumn = (gameBoard.getWidth() - 4)/2;
    Piece* tempPiece = new Piece;
    Coordinate spawnPosition(0, spawnColumn);
    if(gameBoard.isLocationFree(spawnPosition, tempPiece)){
        gameBoard.putPiece(spawnPosition, tempPiece);
        currentPiece = tempPiece;
        currentPosition = spawnPosition;
        delete tempPiece;
        canPlace = true;
    }
    else{
        gameOver = true;
        canPlace = false;
    }
    return canPlace;
}

void Game::moveLeft(){
    
}

