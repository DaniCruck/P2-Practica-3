#include <cxxtest/TestSuite.h>

#include <stdexcept>

#include "Gameboard.h"

class TestSuiteACGameboard : public CxxTest::TestSuite {
public:

  void testGameboard() {
    // comprueba tamaño del tablero
    Gameboard board(12, 10);
    TS_ASSERT_EQUALS(board.getHeight(), 12);
    TS_ASSERT_EQUALS(board.getWidth(), 10);

    // comprueba tablero pequeño
    TS_ASSERT_THROWS(Gameboard(9, 10), std::invalid_argument);
    TS_ASSERT_THROWS(Gameboard(10, 9), std::invalid_argument);

    // comprueba get y set
    Shape::setSeqPieceTypes("O");
    Piece piece;
    TS_ASSERT_EQUALS(board.getContent(3, 4), nullptr);
    board.setContent(3, 4, &piece);
    TS_ASSERT_EQUALS(board.getContent(3, 4), &piece);
    board.setContent(3, 4, nullptr);
    TS_ASSERT_EQUALS(board.getContent(3, 4), nullptr);

    // comprueba ubicación correcta
    TS_ASSERT(board.isLocationFree(Coordinate(0, 0), &piece));
    TS_ASSERT(!board.isLocationFree(Coordinate(11, 9), &piece));

    // comprueba colocar y quitar pieza
    Coordinate origin(4, 3);
    board.putPiece(origin, &piece);
    TS_ASSERT_DIFFERS(board.getContent(4, 4), nullptr);
    TS_ASSERT_DIFFERS(board.getContent(5, 5), nullptr);
    board.removePiece(&piece);
    TS_ASSERT_EQUALS(board.getContent(4, 4), nullptr);
    TS_ASSERT_EQUALS(board.getContent(5, 5), nullptr);

    // comprueba casilla ocupada
    Shape::setSeqPieceTypes("OO");
    Piece fixedPiece;
    Piece movingPiece;
    fixedPiece.setFixed(true);
    board.putPiece(origin, &fixedPiece);
    TS_ASSERT(!board.isLocationFree(origin, &movingPiece));
    TS_ASSERT(board.isLocationFree(Coordinate(0, 0), &movingPiece));
  }
};
