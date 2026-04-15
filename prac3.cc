#include <iostream>
#include "Game.h"

using namespace std;

int main(){
    srand(777); // Inicializar generador de números aleatorios
    string linea;
    Shape::setSeqPieceTypes("OSLOJIZOT"); // Secuencia inicial de piezas, luego aleatorias
    Game game(12,10);
    
    game.nextPiece();
    do{
        cout << game;
        cout << "Orden: ";
        getline(cin,linea);
        
        // El espacio en blanco se interpreta como "bajar pieza"
        if(linea==""){
            game.moveDown();
            // Chequear fixed + nextPiece + gameOver
            if(game.isPieceFixed()){
                game.nextPiece();
                if(game.isGameOver()){
                    cout << game << endl << "GAME OVER!!" << endl;
                    break;
                }
            }
        }
        else if (linea == "L" || linea == "l"){
            game.moveLeft();
        }
        else if (linea == "R" || linea == "r"){
            game.moveRight();
        }
        else if (linea == "U" || linea == "u"){
            game.rotateCounterClockwise();
        }
        else if (linea == "D" || linea == "d"){
            game.rotateClockwise();
        }
        
    } while (linea != "q");
}
