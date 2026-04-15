#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>

using namespace std;

const unsigned int kSHAPESIZE=4;
const unsigned int kNUMPIECES=7;
const string kLETTERS="IJLOSZT";

enum Orientation{D0,D270,D180,D90};
enum PieceType{PT_I,PT_J,PT_L,PT_O,PT_S,PT_Z,PT_T};

class Shape{
    private:
        static string seqPieceTypes;
        static unsigned int idxSeqPieceTypes;
        static PieceType convertFromChar(char c);
    public:
        static void setSeqPieceTypes(string s);
        static PieceType getRandomPieceType();
        static int** getShape(Orientation o,PieceType pt);
        static char convertToChar(PieceType pt);
};

#endif