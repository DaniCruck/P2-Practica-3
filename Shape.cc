#include <ctype.h> // Para rand()
#include "Shape.h"

using namespace std;

// Inicializamos atributos estáticos
string Shape::seqPieceTypes="";
unsigned int Shape::idxSeqPieceTypes=0;

// 0 grados
const int shapeD0[kNUMPIECES][kSHAPESIZE][kSHAPESIZE]={
    { 0, 0, 0, 0,    1, 1, 1, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // I
    { 1, 0, 0, 0,    1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // J
    { 0, 0, 1, 0,    1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // L
    { 0, 1, 1, 0,    0, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // O
    { 0, 1, 1, 0,    1, 1, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // S
    { 1, 1, 0, 0,    0, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // Z
    { 0, 1, 0, 0,    1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }  // T
};

// 90 grados
const int shapeD90[kNUMPIECES][kSHAPESIZE][kSHAPESIZE]={
    { 0, 1, 0, 0,    0, 1, 0, 0,    0, 1, 0, 0,    0, 1, 0, 0 }, // I
    { 0, 1, 0, 0,    0, 1, 0, 0,    1, 1, 0, 0,    0, 0, 0, 0 }, // J
    { 1, 1, 0, 0,    0, 1, 0, 0,    0, 1, 0, 0,    0, 0, 0, 0 }, // L
    { 0, 1, 1, 0,    0, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // O
    { 1, 0, 0, 0,    1, 1, 0, 0,    0, 1, 0, 0,    0, 0, 0, 0 }, // S
    { 0, 1, 0, 0,    1, 1, 0, 0,    1, 0, 0, 0,    0, 0, 0, 0 }, // Z
    { 0, 1, 0, 0,    1, 1, 0, 0,    0, 1, 0, 0,    0, 0, 0, 0 }  // T
};

// 180 grados
const int shapeD180[kNUMPIECES][kSHAPESIZE][kSHAPESIZE]={
    { 0, 0, 0, 0,    0, 0, 0, 0,    1, 1, 1, 1,    0, 0, 0, 0 }, // I
    { 0, 0, 0, 0,    1, 1, 1, 0,    0, 0, 1, 0,    0, 0, 0, 0 }, // J
    { 0, 0, 0, 0,    1, 1, 1, 0,    1, 0, 0, 0,    0, 0, 0, 0 }, // L
    { 0, 1, 1, 0,    0, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // O
    { 0, 0, 0, 0,    0, 1, 1, 0,    1, 1, 0, 0,    0, 0, 0, 0 }, // S
    { 0, 0, 0, 0,    1, 1, 0, 0,    0, 1, 1, 0,    0, 0, 0, 0 }, // Z
    { 0, 0, 0, 0,    1, 1, 1, 0,    0, 1, 0, 0,    0, 0, 0, 0 }  // T
};

// 270 grados
const int shapeD270[kNUMPIECES][kSHAPESIZE][kSHAPESIZE]={
    { 0, 0, 1, 0,    0, 0, 1, 0,    0, 0, 1, 0,    0, 0, 1, 0 }, // I
    { 0, 1, 1, 0,    0, 1, 0, 0,    0, 1, 0, 0,    0, 0, 0, 0 }, // J
    { 0, 1, 0, 0,    0, 1, 0, 0,    0, 1, 1, 0,    0, 0, 0, 0 }, // L
    { 0, 1, 1, 0,    0, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // O
    { 0, 1, 0, 0,    0, 1, 1, 0,    0, 0, 1, 0,    0, 0, 0, 0 }, // S
    { 0, 0, 1, 0,    0, 1, 1, 0,    0, 1, 0, 0,    0, 0, 0, 0 }, // Z
    { 0, 1, 0, 0,    0, 1, 1, 0,    0, 1, 0, 0,    0, 0, 0, 0 }  // T
};

/*
Función que convierte un carácter a su correspondiente PieceType
c: Carácter a convertir
return: PieceType correspondiente al carácter "c". Si "c" no es un carácter válido, se devuelve "PT_I"
*/
PieceType Shape::convertFromChar(char c){
    PieceType pType=PT_I; // Valor por defecto. No debería usarse si "c" es correcto
    bool found=false;

    for(unsigned int i=0;i<kLETTERS.length() && !found;i++){
        if(kLETTERS[i]==c){
            pType=(PieceType)i;
            found=true;
        }
    }

    return pType;
}

/*
Función que establece la secuencia de piezas a generar antes de que se generen aleatoriamente
s: Secuencia de caracteres que representan las piezas a generar
return: nada
*/
void Shape::setSeqPieceTypes(string s){
    seqPieceTypes=s;
    idxSeqPieceTypes=0;
}

/*
Función que devuelve un PieceType aleatorio o de la secuencia establecida
return: PieceType aleatorio o de la secuencia establecida
*/
PieceType Shape::getRandomPieceType(){
    PieceType piece;

    if(idxSeqPieceTypes<seqPieceTypes.length()){
        piece=convertFromChar(seqPieceTypes[idxSeqPieceTypes]);
        idxSeqPieceTypes++;
    }
    else{
        piece=(PieceType)(rand()%kNUMPIECES);
    }

    return piece;
}

/*
Función que devuelve la matriz de 4x4 correspondiente a una pieza y orientación dadas
o: Orientación de la pieza
pt: Tipo de pieza
return: Matriz de 4x4 correspondiente a la pieza y orientación dadas
*/
int** Shape::getShape(Orientation o,PieceType pt){
    int **mat=new int*[kSHAPESIZE]; // Reservamos memoria dinámica para la matriz
    
    for(unsigned int i=0;i<kSHAPESIZE;i++){
        mat[i]=new int[kSHAPESIZE];
        
        for(unsigned int j=0;j<kSHAPESIZE;j++){
            switch(o){
                case D0: mat[i][j]=shapeD0[pt][i][j];
                    break;
                case D90: mat[i][j]=shapeD90[pt][i][j];
                    break;
                case D180: mat[i][j]=shapeD180[pt][i][j];
                    break;
                case D270: mat[i][j]=shapeD270[pt][i][j];
            }
        }
    }

    return mat;
}

/*
Función que convierte un PieceType a su correspondiente carácter
pt: PieceType a convertir
return: Carácter correspondiente al PieceType "pt". Si "pt" no es un tipo de pieza válido, se devuelve "I" (valor por defecto)
*/
char Shape::convertToChar(PieceType pt){
    char letter='I';
    
    if(pt>=0 && pt<kNUMPIECES){
        letter=kLETTERS[pt];
    }
     
    return letter;
}
